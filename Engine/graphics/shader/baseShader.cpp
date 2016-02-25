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

#include "baseShader.h"

#include <string>
#include "../../platform/types.h"
#include "../../engine/entity.h"
#include "../../engine/light/light.h"

BaseShader::BaseShader() : ShaderProgram(FilePath::getFileFromGamePath("bin" + std::string(PATH_SEPARATOR) + "shader" + std::string(PATH_SEPARATOR) + "baseShader.vs"), FilePath::getFileFromGamePath("bin" + std::string(PATH_SEPARATOR) + "shader" + std::string(PATH_SEPARATOR) + "baseShader.fs"))
{}

BaseShader::~BaseShader() {}

void BaseShader::bindAttributes()
{
	bindAttribute(0, "position");
	bindAttribute(1, "textureVector");
	bindAttribute(2, "normalVector");
}

void BaseShader::getAllUniformLocations()
{
	loc_mainColor = getUniformLocation((char*) "mainColor");

	loc_transformationMatrix = getUniformLocation((char*) "transformationMatrix");
	loc_projectionMatrix = getUniformLocation((char*) "projectionMatrix");
	loc_viewMatrix = getUniformLocation((char*) "viewMatrix");

	loc_textured = getUniformLocation((char*) "textured");

	loc_sampler = getUniformLocation((char*) "sampler");

	loc_bgColor = getUniformLocation((char*) "bgColor");
	loc_ambientColor = getUniformLocation((char*) "ambientColor");

	loc_tilingX = getUniformLocation((char*) "tilingX");
	loc_tilingY = getUniformLocation((char*) "tilingY");

	loc_density = getUniformLocation((char*) "density");
	loc_gradient = getUniformLocation((char*) "gradient");

	loc_lightType[0] = getUniformLocation((char*) "lightType[0]");
	loc_lightType[1] = getUniformLocation((char*) "lightType[1]");
	loc_lightType[2] = getUniformLocation((char*) "lightType[2]");
	loc_lightType[3] = getUniformLocation((char*) "lightType[3]");

	loc_lightColor[0] = getUniformLocation((char*) "lightColor[0]");
	loc_lightColor[1] = getUniformLocation((char*) "lightColor[1]");
	loc_lightColor[2] = getUniformLocation((char*) "lightColor[2]");
	loc_lightColor[3] = getUniformLocation((char*) "lightColor[3]");

	loc_lightIntensity[0] = getUniformLocation((char*) "lightIntensity[0]");
	loc_lightIntensity[1] = getUniformLocation((char*) "lightIntensity[1]");
	loc_lightIntensity[2] = getUniformLocation((char*) "lightIntensity[2]");
	loc_lightIntensity[3] = getUniformLocation((char*) "lightIntensity[3]");

	loc_lightPosition[0] = getUniformLocation((char*) "lightPosition[0]");
	loc_lightPosition[1] = getUniformLocation((char*) "lightPosition[1]");
	loc_lightPosition[2] = getUniformLocation((char*) "lightPosition[2]");
	loc_lightPosition[3] = getUniformLocation((char*) "lightPosition[3]");

	loc_lightRange[0] = getUniformLocation((char*) "lightRange[0]");
	loc_lightRange[1] = getUniformLocation((char*) "lightRange[1]");
	loc_lightRange[2] = getUniformLocation((char*) "lightRange[2]");
	loc_lightRange[3] = getUniformLocation((char*) "lightRange[3]");

	loc_lightDir[0] = getUniformLocation((char*) "lightDir[0]");
	loc_lightDir[1] = getUniformLocation((char*) "lightDir[1]");
	loc_lightDir[2] = getUniformLocation((char*) "lightDir[2]");
	loc_lightDir[3] = getUniformLocation((char*) "lightDir[3]");
}

void BaseShader::loadColor(Color3 *value)
{
	Vector3 *cl = new Vector3(value->r, value->g, value->b);

	loadVector3(loc_mainColor, cl);
}

void BaseShader::loadTransformationMatrix(Matrix4 *value)
{
	loadMatrix4(loc_transformationMatrix, value);
}

void BaseShader::loadProjectionMatrix(Matrix4 *value)
{
	loadMatrix4(loc_projectionMatrix, value);
}

void BaseShader::loadViewMatrix(Matrix4 *value)
{
	loadMatrix4(loc_viewMatrix, value);
}

void BaseShader::loadTextured(bool value)
{
	loadBoolean(loc_textured, value);
}

void BaseShader::loadBackgroundColor(Color3 *value)
{
	Vector3 *cl = new Vector3(value->r, value->g, value->b);

	loadVector3(loc_bgColor, cl);
}

void BaseShader::loadAmbientColor(Color3 *value)
{
	Vector3 *cl = new Vector3(value->r, value->g, value->b);

	loadVector3(loc_ambientColor, cl);
}

void BaseShader::loadTiling(F32 value1, F32 value2)
{
	loadFloat(loc_tilingX, value1);
	loadFloat(loc_tilingY, value2);
}

void BaseShader::loadFogSettings(F32 value1, F32 value2)
{
	loadFloat(loc_density, value1);
	loadFloat(loc_gradient, value2);
}

Vector3 *BaseShader::getLightDirection(Vector3 *lightRotation)
{
	Vector3 *lightDirection = new Vector3();

	lightDirection->x = cosf(lightRotation->y - 180.0f) * cosf(lightRotation->x - 180.0f);
	lightDirection->y = sinf(lightRotation->y - 180.0f) * cosf(lightRotation->x - 180.0f);
	lightDirection->z = sinf(lightRotation->x - 180.0f);

	return lightDirection;
}

void BaseShader::loadLightSources(Light *lightSources[4])
{
	for(U16 i = 0; i < 4; i++)
	{
		if(lightSources[i] == nullptr)
		{
			loadInt(loc_lightType[i], 0);
			continue;
		}

		U16 type;

		if(lightSources[i]->type == "DirectionalLight") type = 1;
		else if(lightSources[i]->type == "PointLight") type = 2;
		else if(lightSources[i]->type == "SpotLight") type = 3;

		loadInt(loc_lightType[i], (S32) type);

		Vector3 *color = new Vector3(lightSources[i]->color->r, lightSources[i]->color->g, lightSources[i]->color->b);

		loadVector3(loc_lightColor[i], color);

		F32 intens = lightSources[i]->intensity;

		if(intens < 0.0f) intens = 0.0f;
		if(intens > 15.0f) intens = 15.0f;

		loadFloat(loc_lightIntensity[i], intens);

		TransformComponent *transformComponent = (TransformComponent*) lightSources[i]->entity->getComponent("TransformComponent");

		if(type == 2 || type == 3) loadVector3(loc_lightPosition[i], transformComponent->position);
		else loadVector3(loc_lightPosition[i], new Vector3());

		if(type == 1)
		{
			DirectionalLight *directionalLight = (DirectionalLight*) lightSources[i];

			TransformComponent *transformComponent = (TransformComponent*) directionalLight->entity->getComponent("TransformComponent");

			loadVector3(loc_lightDir[i], getLightDirection(transformComponent->rotation));
		}
		if(type == 2)
		{
			PointLight *pointLight = (PointLight*) lightSources[i];
			loadFloat(loc_lightRange[i], pointLight->range);
			loadVector3(loc_lightDir[i], new Vector3());
		}
		else if(type == 3)
		{
			SpotLight *spotLight = (SpotLight*) lightSources[i];
			loadFloat(loc_lightRange[i], spotLight->range);

			TransformComponent *transformComponent = (TransformComponent*) spotLight->entity->getComponent("TransformComponent");

			loadVector3(loc_lightDir[i], getLightDirection(transformComponent->rotation));
		}
		else
		{
			loadFloat(loc_lightRange[i], 0.0f);
			loadVector3(loc_lightDir[i], new Vector3());
		}
	}
}
