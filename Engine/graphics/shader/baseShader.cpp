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

char *binFolder = FilePath::getGamePath();

std::string vsPath = "bin" + std::string(PATH_SEPARATOR) + "shader" + std::string(PATH_SEPARATOR) + "baseShader.vs";
std::string fsPath = "bin" + std::string(PATH_SEPARATOR) + "shader" + std::string(PATH_SEPARATOR) + "baseShader.fs";

std::string vsPathFull = binFolder + vsPath;
std::string fsPathFull = binFolder + fsPath;

BaseShader::BaseShader() : ShaderProgram(new FilePath(vsPathFull), new FilePath(fsPathFull))
{}

void BaseShader::bindAttributes()
{
	bindAttribute(0, "position");
	bindAttribute(1, "textureVector");
	bindAttribute(2, "normalVector");
}

void BaseShader::getAllUniformLocations()
{
	loc_mainColor = getUniformLocation("mainColor");

	loc_transformationMatrix = getUniformLocation("transformationMatrix");
	loc_projectionMatrix = getUniformLocation("projectionMatrix");
	loc_viewMatrix = getUniformLocation("viewMatrix");

	loc_textured = getUniformLocation("textured");

	loc_sampler = getUniformLocation("sampler");

	loc_bgColor = getUniformLocation("bgColor");
	loc_ambientColor = getUniformLocation("ambientColor");

	loc_tilingX = getUniformLocation("tilingX");
	loc_tilingY = getUniformLocation("tilingY");
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
