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
#include "shader/baseShader.h"
#include "shader/skyboxShader.h"
#include "../error/error.h"
#include "../engine/game/game.h"
#include "../window/window.h"

Matrix4 *projectionMatrix = NULL;
Matrix4 *viewMatrix = NULL;

#include <iostream> //TODO remove after testing

/* Shaders */
BaseShader *baseShader = NULL;
SkyboxShader *skyboxShader = NULL;

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

	std::string msg;
	FilePath *file;
	S16 size;
	Vector2 *pos;
	Color3 *color;
};

static std::vector<Text2D*> textsToRender;

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
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
}

void GraphicsDevice::init()
{
	baseShader = getBaseShader();
	skyboxShader = getSkyboxShader();

	clear();

	Window::update();
}

void GraphicsDevice::render(Scene *scene)
{
	if(isGameRunning() == false) return;

	if(scene == NULL) return;

	if(scene->camera == NULL || scene->camera->entity == NULL) return;

	projectionMatrix = CameraComponent::createProjectionMatrix(scene->camera);
	viewMatrix = CameraComponent::createViewMatrix(scene->camera);

	baseShader->start();
	baseShader->loadProjectionMatrix(projectionMatrix);
	baseShader->loadViewMatrix(viewMatrix);
	baseShader->loadBackgroundColor(scene->backgroundColor);
	baseShader->loadFogSettings(scene->fogDensity, scene->fogGradient);
	baseShader->stop();

	prepare3D();

	if(scene->backgroundColor == NULL) clear(new Color3());
	else clear(scene->backgroundColor);

	for(U32 i = 0; i < scene->entities.size(); i++)
	{
		if(scene->entities.at(i)->children.size() > 0)
		{
			for(U32 j = 0; j < scene->entities.at(i)->children.size(); j++)
			{
				if(scene->entities.at(i)->children.at(j)->hasComponent("MeshRendererComponent"))
				{
					MeshRendererComponent *meshRendererComponent = (MeshRendererComponent*) scene->entities.at(i)->children.at(j)->getComponent("MeshRendererComponent");

					if(meshRendererComponent->model != NULL)
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

			if(meshRendererComponent->model != NULL)
			{
				startBaseShader(scene->entities.at(i), scene);

				renderEntity(scene->entities.at(i), meshRendererComponent);

				stopBaseShader();
			}
		}
	}

	if(scene->skybox != NULL)
	{
		startSkyboxShader(scene);
		renderSkybox(scene->skybox);
		stopSkyboxShader();
	}

	if(textsToRender.size() > 0)
	{
		for(U32 i = 0; i < textsToRender.size(); i++)
		{
			SDL_Color color = { (U8)textsToRender.at(i)->color->r, (U8)textsToRender.at(i)->color->g, (U8)textsToRender.at(i)->color->b };

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			gluOrtho2D(0, Window::getWidth(), Window::getHeight(), 0);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			glDisable(GL_DEPTH_TEST);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			TTF_Font *m_font = TTF_OpenFont(textsToRender.at(i)->file->getPath().c_str(), textsToRender.at(i)->size);

			if(!m_font && isGameRunning() == true) Error::throwError((char*) "Cannot load font file!");

			SDL_Surface *sFont = TTF_RenderText_Blended(m_font, textsToRender.at(i)->msg.c_str(), color);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sFont->w, sFont->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sFont->pixels);

			glBegin(GL_QUADS);
			{
				glTexCoord2f(0.0f, 0.0f); glVertex2f(textsToRender.at(i)->pos->x, textsToRender.at(i)->pos->y);
				glTexCoord2f(1.0f, 0.0f); glVertex2f(textsToRender.at(i)->pos->x + sFont->w, textsToRender.at(i)->pos->y);
				glTexCoord2f(1.0f, 1.0f); glVertex2f(textsToRender.at(i)->pos->x + sFont->w, textsToRender.at(i)->pos->y + sFont->h);
				glTexCoord2f(0.0f, 1.0f); glVertex2f(textsToRender.at(i)->pos->x, textsToRender.at(i)->pos->y + sFont->h);
			}
			glEnd();

			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_DEPTH_TEST);

			glMatrixMode(GL_PROJECTION);

			glDeleteTextures(1, &texture);
			TTF_CloseFont(m_font);
			SDL_FreeSurface(sFont);
		}

		textsToRender.clear();
	}

	Window::update();
}

void GraphicsDevice::renderEntity(Entity *entity, MeshRendererComponent *component)
{
	bool textured = false;

	if(entity->hasComponent("MaterialComponent"))
	{
		MaterialComponent *materialComponent = (MaterialComponent*) entity->getComponent("MaterialComponent");

		if(materialComponent->material != NULL && materialComponent->material->texture != NULL) textured = true;
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

		if(!materialComponent->material->texture->surface) Error::throwError("Cannot load texture file!");

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
		if(!skybox->surface[i]) Error::throwError("Cannot load skybox!");

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

void GraphicsDevice::startBaseShader(Entity *entity, Scene *scene)
{
	baseShader->start();

	TransformComponent *transformComponent;

	if(entity->parent == NULL) transformComponent = (TransformComponent*) entity->getComponent("TransformComponent");
	else
	{
		TransformComponent *childTransformComponent = (TransformComponent*) entity->getComponent("TransformComponent");
		TransformComponent *parentTransformComponent = (TransformComponent*) entity->parent->getComponent("TransformComponent");

		Vector3 *finalPos = new Vector3(parentTransformComponent->position->x + childTransformComponent->position->x, parentTransformComponent->position->y + childTransformComponent->position->y, parentTransformComponent->position->z + childTransformComponent->position->z);
		Vector3 *finalRotation = new Vector3(parentTransformComponent->rotation->x + childTransformComponent->rotation->x, parentTransformComponent->rotation->y + childTransformComponent->rotation->y, parentTransformComponent->rotation->z + childTransformComponent->rotation->z);
		Vector3 *finalScale = new Vector3((1.0f - parentTransformComponent->scale->x) + childTransformComponent->scale->x, (1.0f - parentTransformComponent->scale->y) + childTransformComponent->scale->y, (1.0f - parentTransformComponent->scale->z) + childTransformComponent->scale->z);

		transformComponent = new TransformComponent(finalPos, finalRotation, finalScale);
	}


	if(entity->hasComponent("MaterialComponent"))
	{
		MaterialComponent *materialComponent = (MaterialComponent*) entity->getComponent("MaterialComponent");

		if(materialComponent->material != NULL && materialComponent->material->mainColor != NULL) baseShader->loadColor(materialComponent->material->mainColor);
		else baseShader->loadColor(MaterialAsset::getDefaultMainColor());

		if(materialComponent->material != NULL && materialComponent->material->texture != NULL)
		{
			baseShader->loadTextured(true);
			baseShader->loadTiling(materialComponent->material->texture->tilingX, materialComponent->material->texture->tilingY);
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

	baseShader->loadTransformationMatrix(TransformComponent::createTransformationMatrix(transformComponent));
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

/*
void GraphicsDevice::render(Scene *scene)
{
	if(scene->camera == NULL || scene->camera->entity == NULL) return;

	prepare3D();

	if(scene->backgroundColor == NULL) clear(new Color3(0.0f));
	else clear(scene->backgroundColor);

	//TransformComponent *cameraTransformComponent = (TransformComponent*) scene->camera->entity->getComponent("TransformComponent");

	for(U32 i = 0; i < scene->entities.size(); i++)
	{
		TransformComponent *transformComponent = (TransformComponent*) scene->entities.at(i)->getComponent("TransformComponent");

		if(scene->entities.at(i)->hasComponent("MeshRendererComponent"))
		{
			MeshRendererComponent *meshRendererComponent = (MeshRendererComponent*) scene->entities.at(i)->getComponent("MeshRendererComponent");

			if(meshRendererComponent->model != NULL)
			{
				baseShader->start();

				bool modelHasTexture = hasTexture(scene->entities.at(i));

				baseShader->loadTextureState(modelHasTexture);

				baseShader->loadColor(getColor(scene->entities.at(i)));
				baseShader->loadAmbientColor(scene->ambientLightColor);

				baseShader->loadTransformationMatrix(TransformComponent::createTransformationMatrix(transformComponent));
				baseShader->loadProjectionMatrix(CameraComponent::createProjectionMatrix(scene->camera));
				baseShader->loadViewMatrix(CameraComponent::createViewMatrix(scene->camera));

				renderElements(meshRendererComponent, modelHasTexture);

				baseShader->stop();
			}
		}

		if(scene->entities.at(i)->children.size() > 1)
		{
			renderChildren(scene->entities.at(i)->children, transformComponent, scene);
		}
	}

	Window::update();
}

void GraphicsDevice::renderChildren(std::vector<Entity*> children, TransformComponent *parentTransform, Scene *scene)
{
	for(U32 i = 0; i < children.size(); i++)
	{
		TransformComponent *childrenTransform = (TransformComponent*) children.at(i)->getComponent("TransformComponent");

		if(children.at(i)->hasComponent("MeshRendererComponent"))
		{
			MeshRendererComponent *meshRendererComponent = (MeshRendererComponent*) children.at(i)->getComponent("MeshRendererComponent");

			if(meshRendererComponent->model != NULL)
			{
				baseShader->start();

				bool modelHasTexture = hasTexture(children.at(i));

				baseShader->loadTextureState(modelHasTexture);

				Matrix4 *transformationMatrix = TransformComponent::createTransformationMatrix(parentTransform);
				transformationMatrix->translate(childrenTransform->position);
				transformationMatrix->rotate(new Vector3(1.0f, 0.0f, 0.0f), MathUtil::degToRad(childrenTransform->rotation->x));
				transformationMatrix->rotate(new Vector3(0.0f, 1.0f, 0.0f), MathUtil::degToRad(childrenTransform->rotation->y));
				transformationMatrix->rotate(new Vector3(0.0f, 0.0f, 1.0f), MathUtil::degToRad(childrenTransform->rotation->z));
				transformationMatrix->scale(childrenTransform->scale);

				baseShader->loadColor(getColor(children.at(i)));
				baseShader->loadAmbientColor(scene->ambientLightColor);

				baseShader->loadTransformationMatrix(transformationMatrix);
				baseShader->loadProjectionMatrix(CameraComponent::createProjectionMatrix(scene->camera));
				baseShader->loadViewMatrix(CameraComponent::createViewMatrix(scene->camera));

				renderElements(meshRendererComponent, modelHasTexture);

				baseShader->stop();
			}
		}

		if(children.at(i)->children.size() > 1)
		{
			renderChildren(children.at(i)->children, childrenTransform, scene);
		}
	}
}

void GraphicsDevice::renderElements(MeshRendererComponent *meshRendererComponent, bool textured)
{
	if(meshRendererComponent->cullFaces)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}

	glBindVertexArray(meshRendererComponent->model->vaoID);
	glEnableVertexAttribArray(0);
	if(textured) glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	if(textured)
	{
		glActiveTexture(GL_TEXTURE0);
		MaterialComponent *materialComponent = (MaterialComponent*) meshRendererComponent->entity->getComponent("MaterialComponent");
		glBindTexture(GL_TEXTURE_2D, materialComponent->material->texture->textureID);
	}

	glDrawElements(GL_TRIANGLES, meshRendererComponent->model->vertexCount, GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	if(textured) glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);

	if(meshRendererComponent->cullFaces)
	{
		glDisable(GL_CULL_FACE);
	}

}

Color3 *GraphicsDevice::getColor(Entity *entity)
{
	Color3 *color = new Color3(0.6f);

	if(entity->hasComponent("MaterialComponent"))
	{
		MaterialComponent *materialC = (MaterialComponent*) entity->getComponent("MaterialComponent");

		if(materialC->material == NULL) return color;

		if(materialC->material->mainColor == NULL) return color;

		color = materialC->material->mainColor;
	}

	return color;
}*/

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
