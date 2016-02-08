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

#include "vertexArrayObject.h"

#include <GL/glew.h>

std::vector<U32> vaos;
std::vector<U32> vbos;

U32 createVAO()
{
	U32 vao;

	glGenVertexArrays(1, &vao);

	vaos.push_back(vao);

	glBindVertexArray(vao);

	return vao;
}

void storeF32(U32 attributeNumber, U16 size, std::vector<F32> data)
{
	U32 vbo;

	glGenBuffers(1, &vbo);

	vbos.push_back(vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(F32), &data[0], GL_STATIC_DRAW);

	glVertexAttribPointer(attributeNumber, size, GL_FLOAT, false, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void storeIndices(std::vector<U32> data)
{
	U32 vbo;

	glGenBuffers(1, &vbo);

	vbos.push_back(vbo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(U32), &data[0], GL_STATIC_DRAW);
}

U32 VertexArrayObject::loadToVAO(std::vector<F32> positions, S16 dimension)
{
	U32 vaoID = createVAO();

	storeF32(0, dimension, positions);

	glBindVertexArray(0);

	return vaoID;
}

U32 VertexArrayObject::loadToVAO(std::vector<F32> vertices, std::vector<F32> normals, std::vector<U32> indices)
{
	U32 vaoID = createVAO();

	storeIndices(indices);
	storeF32(0, 3, vertices);
	storeF32(2, 3, normals);

	glBindVertexArray(0);

	return vaoID;
}

U32 VertexArrayObject::loadToVAO(std::vector<F32> vertices, std::vector<F32> textureVectors, std::vector<F32> normals, std::vector<U32> indices)
{
	U32 vaoID = createVAO();

	storeIndices(indices);
	storeF32(0, 3, vertices);
	storeF32(1, 2, textureVectors);
	storeF32(2, 3, normals);

	glBindVertexArray(0);

	return vaoID;
}

void VertexArrayObject::destroyAll()
{
	for(U32 i = 0; i < vbos.size(); i++)
	{
		glDeleteBuffers(1, &vbos.at(i));
	}

	for(U32 i = 0; i < vaos.size(); i++)
	{
		glDeleteVertexArrays(1, &vaos.at(i));
	}
}
