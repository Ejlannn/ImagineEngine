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

#include "skyboxShader.h"

#include <string>
#include "../../platform/types.h"

SkyboxShader::SkyboxShader() : ShaderProgram(FilePath::getFileFromGamePath("bin" + std::string(PATH_SEPARATOR) + "shader" + std::string(PATH_SEPARATOR) + "skyboxShader.vs"), FilePath::getFileFromGamePath("bin" + std::string(PATH_SEPARATOR) + "shader" + std::string(PATH_SEPARATOR) + "skyboxShader.fs"))
{}

SkyboxShader::~SkyboxShader() {}

void SkyboxShader::bindAttributes()
{
	bindAttribute(0, "position");
}

void SkyboxShader::getAllUniformLocations()
{
	loc_projectionMatrix = getUniformLocation((char*) "projectionMatrix");
	loc_viewMatrix = getUniformLocation((char*) "viewMatrix");
}

void SkyboxShader::loadProjectionMatrix(Matrix4 *value)
{
	loadMatrix4(loc_projectionMatrix, value);
}

void SkyboxShader::loadViewMatrix(Matrix4 *value)
{
	loadMatrix4(loc_viewMatrix, value);
}
