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

#ifndef _IE_UI_SHADER_H_
#define _IE_UI_SHADER_H_

#include "shaderProgram.h"

class UIShader : public ShaderProgram
{
	friend class GraphicsDevice;

	UIShader();

	~UIShader();

	U32 loc_projectionMatrix;

	virtual void bindAttributes();
	virtual void getAllUniformLocations();

	void loadProjectionMatrix(Matrix4 *value);
};

#endif
