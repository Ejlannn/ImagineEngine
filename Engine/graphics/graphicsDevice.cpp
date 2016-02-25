//Imagine Engine
//Copyright (c) 2016 Szymon 'skprime' Krygier
//
//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "graphicsDevice.h"

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include "lightProcessor.h"
#include "vertexArrayObject.h"
#include "../error/error.h"
#include "../engine/game/game.h"
#include "../ui/uiElementsHandler.h"
#include "../ui/console/console.h"
#include "../window/window.h"

/* Shaders */
#include "shader/baseShader.h"
#include "shader/skyboxShader.h"
#include "shader/uiShader.h"
#include "shader/uinShader.h"

static Matrix4 *projectionMatrix = nullptr;
static Matrix4 *viewMatrix = nullptr;
static Matrix4 *projectionMatrix2DOrtho = nullptr;

static std::vector<UIElement*> elementsToRender;

/* Shaders */
static BaseShader		*baseShader = nullptr;
static SkyboxShader	*skyboxShader = nullptr;
static UIShader		*uiShader = nullptr;
static UINShader		*uinShader = nullptr;

static U16 samplesSize = 8;

struct Text2D
{
public:
	Text2D(const std::string &message, FilePath *fontFile, S16 size, Vector2 *position)
	{
		msg = message;
		file = fontFile;
		this->size = size;
		pos = position;
		color = new Color3(255.0f);
	}

	~Text2D() {}

	std::string msg;
	FilePath *file;
	S16 size;
	Vector2 *pos;
	Color3 *color;
};

static std::vector<Text2D*> textsToRender;

void GraphicsDevice::setSamplesSize(U16 samples)
{
	samplesSize = samples;
}

bool isGameRunning()
{
	return Game::isRunning();
}

void clear(Color3 *color)
{
	glClearColor(color->r, color->g, color->b, 255.0f);
}

void clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	clear(new Color3());
}

void prepare3D()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, (U32) samplesSize);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	glEnable(GL_MULTISAMPLE);
	//glEnable(GL_MULTISAMPLE_ARB);
}

void GraphicsDevice::init()
{
	baseShader = getBaseShader();
	skyboxShader = getSkyboxShader();
	uiShader = getUIShader();
	uinShader = getUINShader();

	clear();

	Window::update();

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
}

void GraphicsDevice::render(Scene *scene)
{
	if(isGameRunning() == false) return;

	if(scene == nullptr) return;

	if(scene->camera == nullptr || scene->camera->entity == nullptr) return;

	projectionMatrix = CameraComponent::createProjectionMatrix(scene->camera);
	projectionMatrix2DOrtho = CameraComponent::create2DOrthoProjectionMatrix();
	viewMatrix = CameraComponent::createViewMatrix(scene->camera);

	baseShader->start();
	baseShader->loadProjectionMatrix(projectionMatrix);
	baseShader->loadViewMatrix(viewMatrix);
	baseShader->loadBackgroundColor(scene->backgroundColor);
	baseShader->loadFogSettings(scene->fogDensity, scene->fogGradient);
	baseShader->stop();

	prepare3D();

	if(scene->backgroundColor == nullptr) clear(new Color3());
	else clear(scene->backgroundColor);

	if(scene->skybox != nullptr)
	{
		startSkyboxShader(scene);
		renderSkybox(scene->skybox);
		stopSkyboxShader();
	}

	for(U32 i = 0; i < scene->entities.size(); i++)
	{
		if(scene->entities.at(i)->children.size() > 0)
		{
			for(U32 j = 0; j < scene->entities.at(i)->children.size(); j++)
			{
				if(scene->entities.at(i)->children.at(j)->hasComponent("MeshRendererComponent"))
				{
					MeshRendererComponent *meshRendererComponent = (MeshRendererComponent*) scene->entities.at(i)->children.at(j)->getComponent("MeshRendererComponent");

					if(meshRendererComponent->model != nullptr)
					{
						startBaseShader(scene->entities.at(i)->children.at(j), scene);

						renderEntity(scene->entities.at(i)->children.at(j), meshRendererComponent);

						stopBaseShader();
					}
				}
			}
		}

		if(scene->entities.at(i)->hasComponent("MeshRendererComponent"))
		{
			MeshRendererComponent *meshRendererComponent = (MeshRendererComponent*) scene->entities.at(i)->getComponent("MeshRendererComponent");

			if(meshRendererComponent->model != nullptr)
			{
				startBaseShader(scene->entities.at(i), scene);

				renderEntity(scene->entities.at(i), meshRendererComponent);

				stopBaseShader();
			}
		}
	}

	elementsToRender = UIElementsHandler::getElements();

	if(elementsToRender.size() > 0)
	{
		for(U32 i = 0; i < elementsToRender.size(); i++)
		{
			startUIShader();

			renderUIElement(elementsToRender.at(i));

			stopUIShader();
		}
	}

	elementsToRender.clear();

	if(textsToRender.size() > 0)
	{
		for(U32 i = 0; i < textsToRender.size(); i++)
		{
			SDL_Color color = { (U8)textsToRender.at(i)->color->r, (U8)textsToRender.at(i)->color->g, (U8)textsToRender.at(i)->color->b };

			TTF_Font *font = TTF_OpenFont(textsToRender.at(i)->file->getPath().c_str(), textsToRender.at(i)->size);

			if(!font && isGameRunning() == true) Error::throwError((char*) "Cannot load font file!");

			SDL_Surface *fontSurface = TTF_RenderText_Blended(font, textsToRender.at(i)->msg.c_str(), color);

			startUIShader();

			renderUIElement(new UIElement(textsToRender.at(i)->pos, fontSurface));

			stopUIShader();

			SDL_FreeSurface(fontSurface);

			TTF_CloseFont(font);
		}

		textsToRender.clear();
	}

	if(Console::isVisible())
	{
		renderConsole();

		SDL_Color color = { 255, 255, 255 };

		FilePath *fontPath = FilePath::getFileFromGamePath("bin" + std::string(PATH_SEPARATOR) + "font" + std::string(PATH_SEPARATOR) + "Consolas.ttf");

		TTF_Font *font = TTF_OpenFont(fontPath->getPath().c_str(), 12);

		std::vector<std::string> consoleLines = Console::getLines();

		for(U16 i = 0; i < consoleLines.size(); i++)
		{
			if(i > 22) break;

			if(!font && isGameRunning() == true) Error::throwError((char*) "Cannot load font file!");

			SDL_Surface *fontSurface = TTF_RenderText_Blended(font, consoleLines.at(consoleLines.size() - 1 - i).c_str(), color);

			startUIShader();

			renderUIElement(new UIElement(new Vector2(3.0f, (F32) (14 * (consoleLines.size() - 1 - i) + 3)), fontSurface));

			stopUIShader();

			SDL_FreeSurface(fontSurface);
		}

		consoleLines.clear();

		if(Console::getCurrentLine().size() > 0)
		{
			SDL_Surface *fontSurface = TTF_RenderText_Blended(font, Console::getCurrentLine().c_str(), color);

			startUIShader();

			renderUIElement(new UIElement(new Vector2(3.0f, 328.0f), fontSurface));

			stopUIShader();

			SDL_FreeSurface(fontSurface);

			TTF_CloseFont(font);
		}

	}

	Window::update();
}

void GraphicsDevice::renderEntity(Entity *entity, MeshRendererComponent *component)
{
	bool textured = false;

	if(entity->hasComponent("MaterialComponent"))
	{
		MaterialComponent *materialComponent = (MaterialComponent*) entity->getComponent("MaterialComponent");

		if(materialComponent->material != nullptr && materialComponent->material->texture != nullptr) textured = true;
	}

	if(component->cullFaces)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}

	if(textured) glEnable(GL_TEXTURE_2D);

	glBindVertexArray(component->model->vaoID);
	glEnableVertexAttribArray(0);
	if(textured) glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//glDrawElements(GL_TRIANGLES, component->model->getVertexCount(), GL_UNSIGNED_INT, 0);

	if(textured)
	{
		MaterialComponent *materialComponent = (MaterialComponent*) entity->getComponent("MaterialComponent");

		if(materialComponent->material->texture->textureID == 0) glGenTextures(1, &materialComponent->material->texture->textureID);

		glBindTexture(GL_TEXTURE_2D, materialComponent->material->texture->textureID);

		if(!materialComponent->material->texture->surface) Error::throwError((char*) "Cannot load texture file!");

		S32 colorMode = GL_RGB;

		if(materialComponent->material->texture->surface->format->BytesPerPixel == 4) colorMode = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, colorMode, materialComponent->material->texture->surface->w, materialComponent->material->texture->surface->h, 0, colorMode, GL_UNSIGNED_BYTE, materialComponent->material->texture->surface->pixels);

	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	    glGenerateMipmap(GL_TEXTURE_2D);

		glActiveTexture(GL_TEXTURE0);

		glUniform1i(baseShader->loc_sampler, 0);

		//SDL_FreeSurface(surface);
	}

	glDrawElements(GL_TRIANGLES, component->model->getVertexCount(), GL_UNSIGNED_INT, 0);

	if(textured)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
	}

	glDisableVertexAttribArray(0);
	if(textured) glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);

	//if(textured) glDisable(GL_TEXTURE_2D);

	if(component->cullFaces)
	{
		glDisable(GL_CULL_FACE);
	}
}

void GraphicsDevice::renderSkybox(SkyboxAsset *skybox)
{
	if(skybox->id == 0) glGenTextures(1, &skybox->id);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->id);

	for(U32 i = 0; i < 6; i++)
	{
		if(!skybox->surface[i]) Error::throwError((char*) "Cannot load skybox!");

		S32 colorMode = GL_RGB;

		if(skybox->surface[i]->format->BytesPerPixel == 4) colorMode = GL_RGBA;

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, colorMode, skybox->surface[i]->w, skybox->surface[i]->h, 0, colorMode, GL_UNSIGNED_BYTE, skybox->surface[i]->pixels);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindVertexArray(skybox->vaoID);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, skybox->getVertexCount());
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void GraphicsDevice::renderUIElement(UIElement *element)
{
	U32 texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::vector<F32> positions;

	positions.push_back(element->position->x);
	positions.push_back(element->position->y);
	positions.push_back(element->position->x + element->surface->w);
	positions.push_back(element->position->y);
	positions.push_back(element->position->x + element->surface->w);
	positions.push_back(element->position->y + element->surface->h);
	positions.push_back(element->position->x);
	positions.push_back(element->position->y + element->surface->h);

	std::vector<F32> textureCoords;

	textureCoords.push_back(0.0f);
	textureCoords.push_back(0.0f);
	textureCoords.push_back(1.0f);
	textureCoords.push_back(0.0f);
	textureCoords.push_back(1.0f);
	textureCoords.push_back(1.0f);
	textureCoords.push_back(0.0f);
	textureCoords.push_back(1.0f);

	U32 vaoID = VertexArrayObject::loadToVAO(positions, textureCoords);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLenum textureFormat;

	switch (element->surface->format->BytesPerPixel)
	{
	case 4:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		textureFormat = GL_BGRA;
		else
		textureFormat = GL_RGBA;
		break;
	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		textureFormat = GL_BGR;
		else
		textureFormat = GL_RGB;
		break;
	}

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, element->surface->w, element->surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, element->surface->pixels);

	glTexImage2D(GL_TEXTURE_2D, 0, element->surface->format->BytesPerPixel, element->surface->w, element->surface->h, 0, textureFormat, GL_UNSIGNED_BYTE, element->surface->pixels);

	glBindVertexArray(vaoID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &texture);
}

void GraphicsDevice::renderConsole()
{
	startUINShader(new Color3(0.1f,0.1f,0.1f));

	std::vector<F32> positions;


	/*positions.push_back(0.0f);
	positions.push_back(0.0f);
	positions.push_back((F32)Window::getWidth());
	positions.push_back(0.0f);
	positions.push_back((F32)Window::getWidth());
	positions.push_back((F32) Console::getHeight());
	positions.push_back(0.0f);
	positions.push_back((F32) Console::getHeight());
*/

	positions.push_back(-1.0f);
	positions.push_back(1.0f);
	positions.push_back(1.0f);
	positions.push_back(1.0f);
	positions.push_back(1.0f);
	positions.push_back(0.1f);

	positions.push_back(-1.0f);
	positions.push_back(0.1f);
	positions.push_back(-1.0f);
	positions.push_back(1.0f);
	positions.push_back(1.0f);
	positions.push_back(0.1f);

	/*
	positions.push_back(-1.0f);
	positions.push_back(0.1f);
	positions.push_back(1.0f);
	positions.push_back(0.1f);
	positions.push_back(1.0f);
	positions.push_back(0.1f - 0.05f);

	positions.push_back(-1.0f);
	positions.push_back(0.1f - 0.05f);
	positions.push_back(-1.0f);
	positions.push_back(0.1f);
	positions.push_back(1.0f);
	positions.push_back(0.1f - 0.05f);*/

	U32 vaoID = VertexArrayObject::loadToVAO(positions, 2);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindVertexArray(vaoID);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	glDisable(GL_BLEND);

	stopUINShader();

	startUINShader(new Color3(0.05f,0.05f,0.05f));

	std::vector<F32> positions2;

	positions2.push_back(-1.0f);
	positions2.push_back(0.1f);
	positions2.push_back(1.0f);
	positions2.push_back(0.1f);
	positions2.push_back(1.0f);
	positions2.push_back(0.1f - 0.05f);

	positions2.push_back(-1.0f);
	positions2.push_back(0.1f - 0.05f);
	positions2.push_back(-1.0f);
	positions2.push_back(0.1f);
	positions2.push_back(1.0f);
	positions2.push_back(0.1f - 0.05f);

	U32 vaoID2 = VertexArrayObject::loadToVAO(positions2, 2);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindVertexArray(vaoID2);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	glDisable(GL_BLEND);

	stopUINShader();
}

void GraphicsDevice::startBaseShader(Entity *entity, Scene *scene)
{
	baseShader->start();

	TransformComponent *transformComponent;

	if(entity->parent == nullptr) transformComponent = (TransformComponent*) entity->getComponent("TransformComponent");
	else
	{
		TransformComponent *childTransformComponent = (TransformComponent*) entity->getComponent("TransformComponent");
		TransformComponent *parentTransformComponent = (TransformComponent*) entity->parent->getComponent("TransformComponent");

		Vector3 *finalPos = new Vector3(parentTransformComponent->position->x + childTransformComponent->position->x,
				parentTransformComponent->position->y + childTransformComponent->position->y,
				parentTransformComponent->position->z + childTransformComponent->position->z);
		Vector3 *finalRotation = new Vector3(parentTransformComponent->rotation->x + childTransformComponent->rotation->x,
				parentTransformComponent->rotation->y + childTransformComponent->rotation->y,
				parentTransformComponent->rotation->z + childTransformComponent->rotation->z);
		Vector3 *finalScale = new Vector3((1.0f - parentTransformComponent->scale->x) + childTransformComponent->scale->x,
				(1.0f - parentTransformComponent->scale->y) + childTransformComponent->scale->y,
				(1.0f - parentTransformComponent->scale->z) + childTransformComponent->scale->z);

		transformComponent = new TransformComponent(finalPos, finalRotation, finalScale);
	}

	Matrix4 *transformationMatrix = TransformComponent::createTransformationMatrix(transformComponent);

	MeshRendererComponent *meshRendererComponent = (MeshRendererComponent*) entity->getComponent("MeshRendererComponent");

	std::vector<Vector4*> processedVertices;

	for(U64 i = 0; i < meshRendererComponent->model->vertices.size(); i++)
	{
		Vector4 *vertex = new Vector4(meshRendererComponent->model->vertices.at(i)->x,
				meshRendererComponent->model->vertices.at(i)->y,
				meshRendererComponent->model->vertices.at(i)->z, 1.0);


		Vector4 *result = Vector4::transform(vertex, transformationMatrix);

		processedVertices.push_back(result);
	}

	if(entity->hasComponent("MaterialComponent"))
	{
		MaterialComponent *materialComponent = (MaterialComponent*) entity->getComponent("MaterialComponent");

		if(materialComponent->material != nullptr && materialComponent->material->mainColor != nullptr) baseShader->loadColor(materialComponent->material->mainColor);
		else baseShader->loadColor(MaterialAsset::getDefaultMainColor());

		if(materialComponent->material != nullptr && materialComponent->material->texture != nullptr)
		{
			baseShader->loadTextured(true);
			baseShader->loadTiling(materialComponent->material->tilingX, materialComponent->material->tilingY);
		}
		else
		{
			baseShader->loadTextured(false);
			baseShader->loadTiling(1.0f, 1.0f);
		}
	}
	else
	{
		baseShader->loadColor(MaterialAsset::getDefaultMainColor());
		baseShader->loadTextured(false);
		baseShader->loadTiling(1.0f, 1.0f);
	}

	std::vector<Light*> lightSourcesForEntity = LightProcessor::getLightSourcesForEntity(processedVertices);

	Light *tempLightSources[4];

	for(U16 i = 0; i < 4; i++)
	{
		tempLightSources[i] = lightSourcesForEntity.at(i);
	}

	baseShader->loadLightSources(tempLightSources);
	baseShader->loadTransformationMatrix(transformationMatrix);
	baseShader->loadAmbientColor(scene->ambientLightColor);

}

void GraphicsDevice::stopBaseShader()
{
	baseShader->stop();
}

void GraphicsDevice::startSkyboxShader(Scene *scene)
{
	skyboxShader->start();

	Matrix4 *newViewMatrix = viewMatrix->clone();
	newViewMatrix->m30 = 0.0f;
	newViewMatrix->m31 = 0.0f;
	newViewMatrix->m32 = 0.0f;

	skyboxShader->loadProjectionMatrix(projectionMatrix);
	skyboxShader->loadViewMatrix(newViewMatrix);
}

void GraphicsDevice::stopSkyboxShader()
{
	skyboxShader->stop();
}

void GraphicsDevice::startUIShader()
{
	uiShader->start();

	uiShader->loadProjectionMatrix(projectionMatrix2DOrtho);
}

void GraphicsDevice::stopUIShader()
{
	uiShader->stop();
}

void GraphicsDevice::startUINShader(Color3 *color)
{
	uinShader->start();

	uinShader->loadColor(color);
}

void GraphicsDevice::stopUINShader()
{
	uinShader->stop();
}

void GraphicsDevice::addTextToRender(const std::string &message, FilePath *fontFile, S16 size, Vector2 *position)
{
	textsToRender.push_back(new Text2D(message, fontFile, size, position));
}

BaseShader *GraphicsDevice::getBaseShader()
{
	return new BaseShader();
}

SkyboxShader *GraphicsDevice::getSkyboxShader()
{
	return new SkyboxShader();
}

UIShader *GraphicsDevice::getUIShader()
{
	return new UIShader();
}

UINShader *GraphicsDevice::getUINShader()
{
	return new UINShader();
}
