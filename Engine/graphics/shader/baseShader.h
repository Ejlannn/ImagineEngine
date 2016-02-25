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

#ifndef _IE_BASE_SHADER_H_
#define _IE_BASE_SHADER_H_

#include "shaderProgram.h"
#include "../light.h"

class GraphicsDevice;

class BaseShader : public ShaderProgram
{
	friend class GraphicsDevice;

	BaseShader();

	~BaseShader();

	U32 loc_mainColor;
	U32 loc_transformationMatrix;
	U32 loc_projectionMatrix;
	U32 loc_viewMatrix;
	U32 loc_textured;
	U32 loc_sampler;
	U32 loc_bgColor;
	U32 loc_ambientColor;
	U32 loc_tilingX;
	U32 loc_tilingY;
	U32 loc_density;
	U32 loc_gradient;

	U32 loc_lightType[4];
	U32 loc_lightColor[4];
	U32 loc_lightIntensity[4];
	U32 loc_lightPosition[4];
	U32 loc_lightRange[4];
	U32 loc_lightDir[4];

	virtual void bindAttributes();
	virtual void getAllUniformLocations();

	void loadColor(Color3 *value);
	void loadTransformationMatrix(Matrix4 *value);
	void loadProjectionMatrix(Matrix4 *value);
	void loadViewMatrix(Matrix4 *value);
	void loadTextured(bool value);
	void loadBackgroundColor(Color3 *value);
	void loadAmbientColor(Color3 *value);
	void loadTiling(F32 value1, F32 value2);
	void loadFogSettings(F32 value1, F32 value2);
	void loadLightSources(Light *lightSources[4]);

	Vector3 *getLightDirection(Vector3 *lightRotation);
};

#endif
