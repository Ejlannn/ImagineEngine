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

#include "uinShader.h"

#include <string>
#include "../../platform/types.h"

UINShader::UINShader() : ShaderProgram(FilePath::getFileFromGamePath("bin" + std::string(PATH_SEPARATOR) + "shader" + std::string(PATH_SEPARATOR) + "uinShader.vs"), FilePath::getFileFromGamePath("bin" + std::string(PATH_SEPARATOR) + "shader" + std::string(PATH_SEPARATOR) + "uinShader.fs"))
{}

UINShader::~UINShader() {}

void UINShader::bindAttributes()
{
	bindAttribute(0, "position");
}

void UINShader::getAllUniformLocations()
{
	loc_color = getUniformLocation((char*) "color");
}

void UINShader::loadColor(Color3 value)
{
	Vector3 *toLoad = new Vector3(value.r, value.g, value.b);

	loadVector3(loc_color, toLoad);
}
