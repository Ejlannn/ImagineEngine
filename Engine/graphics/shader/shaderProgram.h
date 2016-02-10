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

#ifndef _IE_SHADER_PROGRAM_H_
#define _IE_SHADER_PROGRAM_H_

#include "../../error/error.h"
#include "../../math/math.h"
#include "../../platform/file.h"
#include "../../platform/types.h"

enum ShaderType
{
	VERTEX_SHADER,
	FRAGMENT_SHADER
};

class GraphicsDevice;

class ShaderProgram
{
	friend class GraphicsDevice;

protected:
	ShaderProgram(FilePath *vertexShader, FilePath *fragmentShader);

	virtual ~ShaderProgram();

	virtual void bindAttributes() = 0;
	virtual void getAllUniformLocations() = 0;

	void bindAttribute(U32 attribute, const std::string &name);

	void loadInt(U32 location, U32 value);
	void loadFloat(U32 location, F32 value);
	void loadVector2(U32 location, Vector2 *value);
	void loadVector3(U32 location, Vector3 *value);
	void loadBoolean(U32 location, bool value);
	void loadMatrix4(U32 location, Matrix4 *value);

	U32 getUniformLocation(char *name);

private:
	U32 shaderProgramID;
	U32 vertexShaderID;
	U32 fragmentShaderID;

	FilePath *vertexFile;
	FilePath *fragmentFile;

	void start();
	void stop();

	void createShaderProgram();
	void deleteShaderProgram();

	U32 loadShader(FilePath *file, ShaderType type);
};

#endif
