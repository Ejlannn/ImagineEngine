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

#ifndef _IE_SKYBOX_SHADER_H_
#define _IE_SKYBOX_SHADER_H_

#include "shaderProgram.h"

class GraphicsDevice;

class SkyboxShader : public ShaderProgram
{
	friend class GraphicsDevice;

private:
	SkyboxShader();

	U32 loc_projectionMatrix;
	U32 loc_viewMatrix;

	virtual void bindAttributes();
	virtual void getAllUniformLocations();

	void loadProjectionMatrix(Matrix4 *value);
	void loadViewMatrix(Matrix4 *value);
};

#endif
