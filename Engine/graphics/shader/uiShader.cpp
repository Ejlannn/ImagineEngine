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

#include "uiShader.h"

#include <string>
#include "../../platform/types.h"

char *binFolder3 = FilePath::getGamePath();

std::string vsPath3 = "bin" + std::string(PATH_SEPARATOR) + "shader" + std::string(PATH_SEPARATOR) + "uiShader.vs";
std::string fsPath3 = "bin" + std::string(PATH_SEPARATOR) + "shader" + std::string(PATH_SEPARATOR) + "uiShader.fs";

std::string vsPathFull3 = binFolder3 + vsPath3;
std::string fsPathFull3 = binFolder3 + fsPath3;

UIShader::UIShader() : ShaderProgram(new FilePath(vsPathFull3), new FilePath(fsPathFull3))
{}

void UIShader::bindAttributes()
{
	bindAttribute(0, "position");
	bindAttribute(1, "textureVector");
}

void UIShader::getAllUniformLocations()
{
	loc_projectionMatrix = getUniformLocation("projectionMatrix");
}

void UIShader::loadProjectionMatrix(Matrix4 *value)
{
	loadMatrix4(loc_projectionMatrix, value);
}
