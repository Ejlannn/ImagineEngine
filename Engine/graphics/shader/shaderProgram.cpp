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

#include "shaderProgram.h"

#include <fstream>
#include <GL/glew.h>
#include "../../error/error.h"

ShaderProgram::ShaderProgram(FilePath *vertexShader, FilePath *fragmentShader)
{
	shaderProgramID = 0;
	vertexShaderID = 0;
	fragmentShaderID = 0;

	this->vertexFile = vertexShader;
	this->fragmentFile = fragmentShader;
}

ShaderProgram::~ShaderProgram()
{
	deleteShaderProgram();
}

void ShaderProgram::start()
{
	if(shaderProgramID == 0) createShaderProgram();

	glUseProgram(shaderProgramID);
}

void ShaderProgram::stop()
{
	glUseProgram(0);
}

void ShaderProgram::createShaderProgram()
{
	if(shaderProgramID != 0) return;

	vertexShaderID = loadShader(vertexFile, ShaderType::VERTEX_SHADER);
	fragmentShaderID = loadShader(fragmentFile, ShaderType::FRAGMENT_SHADER);

	if(vertexShaderID == 0 || fragmentShaderID == 0) Error::throwError("Cannot create shader file");

	shaderProgramID = glCreateProgram();

	glAttachShader(shaderProgramID, vertexShaderID);
	glAttachShader(shaderProgramID, fragmentShaderID);

	bindAttributes();

	glLinkProgram(shaderProgramID);
	glValidateProgram(shaderProgramID);

	getAllUniformLocations();
}

void ShaderProgram::deleteShaderProgram()
{
	stop();

	glDetachShader(shaderProgramID, vertexShaderID);
	glDetachShader(shaderProgramID, fragmentShaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	glDeleteProgram(shaderProgramID);
}

U32 ShaderProgram::loadShader(FilePath *file, ShaderType type)
{
	std::ifstream shaderFile(file->getPath());

	std::string shaderSource;
	std::string tempLine;

	while(std::getline(shaderFile, tempLine))
	{
		shaderSource.append(tempLine + "\n");
	}

	U32 id;

	if(type == ShaderType::VERTEX_SHADER) id = glCreateShader(GL_VERTEX_SHADER);
	else if(type == ShaderType::FRAGMENT_SHADER) id = glCreateShader(GL_FRAGMENT_SHADER);
	else return 0;

	GLchar const *shaderSrc = shaderSource.c_str();
	GLint const shaderLength = shaderSource.size();

	glShaderSource(id, 1, &shaderSrc, &shaderLength);
	glCompileShader(id);

	GLint result;

	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if(result == GL_FALSE) Error::throwErrorCode(4);

	return id;
}

void ShaderProgram::bindAttribute(U32 attribute, const std::string &name)
{
	glBindAttribLocation(shaderProgramID, attribute, name.c_str());
}

void ShaderProgram::loadInt(U32 location, U32 value)
{
	glUniform1i(location, value);
}

void ShaderProgram::loadFloat(U32 location, F32 value)
{
	glUniform1f(location, value);
}

void ShaderProgram::loadVector2(U32 location, Vector2 *value)
{
	glUniform2f(location, value->x, value->y);
}

void ShaderProgram::loadVector3(U32 location, Vector3 *value)
{
	glUniform3f(location, value->x, value->y, value->z);
}

void ShaderProgram::loadVector4(U32 location, Vector4 *value)
{
	glUniform4f(location, value->x, value->y, value->z, value->w);
}

void ShaderProgram::loadBoolean(U32 location, bool value)
{
	U32 toLoad = 0;

	if(value) toLoad = 1;

	glUniform1i(location, toLoad);
}

void ShaderProgram::loadMatrix4(U32 location, Matrix4 *value)
{
	F32 mat[] =
	{
			value->m00, value->m01, value->m02, value->m03,
			value->m10, value->m11, value->m12, value->m13,
			value->m20, value->m21, value->m22, value->m23,
			value->m30, value->m31, value->m32, value->m33,
	};

	glUniformMatrix4fv(location, 1, false, mat);
}

U32 ShaderProgram::getUniformLocation(char *name)
{
	return glGetUniformLocation(shaderProgramID, name);
}
