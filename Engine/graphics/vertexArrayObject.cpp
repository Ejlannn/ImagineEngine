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

struct VAOBuffers
{
	VAOBuffers(U32 vao)
	{
		vaoID = vao;
	}

	U32 vaoID;
	std::vector<U32> buffers;
};

static std::vector<VAOBuffers> vaos;

U32 VertexArrayObject::createVAO()
{
	U32 vao;

	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	return vao;
}

U32 VertexArrayObject::storeF32(U32 attributeNumber, U16 size, std::vector<F32> data)
{
	U32 vbo;

	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(F32), &data[0], GL_STATIC_DRAW);

	glVertexAttribPointer(attributeNumber, size, GL_FLOAT, false, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vbo;
}

U32 VertexArrayObject::storeIndices(std::vector<U64> data)
{
	U32 vbo;

	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(U64), &data[0], GL_STATIC_DRAW);

	return vbo;
}

U32 VertexArrayObject::loadToVAO(std::vector<F32> positions, S16 dimension)
{
	U32 vaoID = createVAO();

	VAOBuffers vaoToAdd = VAOBuffers(vaoID);

	vaoToAdd.buffers.push_back(storeF32(0, dimension, positions));

	vaos.push_back(vaoToAdd);

	glBindVertexArray(0);

	return vaoID;
}

U32 VertexArrayObject::loadToVAO(std::vector<F32> positions, std::vector<F32> textureVectors)
{
	U32 vaoID = createVAO();

	VAOBuffers vaoToAdd = VAOBuffers(vaoID);

	vaoToAdd.buffers.push_back(storeF32(0, 2, positions));
	vaoToAdd.buffers.push_back(storeF32(1, 2, textureVectors));

	vaos.push_back(vaoToAdd);

	glBindVertexArray(0);

	return vaoID;
}

U32 VertexArrayObject::loadToVAO(std::vector<F32> vertices, std::vector<F32> normals, std::vector<U64> indices)
{
	U32 vaoID = createVAO();

	VAOBuffers vaoToAdd = VAOBuffers(vaoID);

	vaoToAdd.buffers.push_back(storeIndices(indices));
	vaoToAdd.buffers.push_back(storeF32(0, 3, vertices));
	vaoToAdd.buffers.push_back(storeF32(2, 3, normals));

	vaos.push_back(vaoToAdd);

	glBindVertexArray(0);

	return vaoID;
}

U32 VertexArrayObject::loadToVAO(std::vector<F32> vertices, std::vector<F32> textureVectors, std::vector<F32> normals, std::vector<U64> indices)
{
	U32 vaoID = createVAO();

	VAOBuffers vaoToAdd = VAOBuffers(vaoID);

	vaoToAdd.buffers.push_back(storeIndices(indices));
	vaoToAdd.buffers.push_back(storeF32(0, 3, vertices));
	vaoToAdd.buffers.push_back(storeF32(1, 2, textureVectors));
	vaoToAdd.buffers.push_back(storeF32(2, 3, normals));

	vaos.push_back(vaoToAdd);

	glBindVertexArray(0);

	return vaoID;
}

void VertexArrayObject::destroy(U32 vao)
{
	for(U32 i = 0; i < vaos.size(); i++)
	{
		if(vaos.at(i).vaoID == vao)
		{
			for(U32 j = 0; j < vaos.at(i).buffers.size(); j++) glDeleteBuffers(1, &vaos.at(i).buffers.at(j));

			glDeleteVertexArrays(1, &vaos.at(i).vaoID);

			break;
		}
	}
}

void VertexArrayObject::destroyAll()
{
	for(U32 i = 0; i < vaos.size(); i++)
	{
		for(U32 j = 0; j < vaos.at(i).buffers.size(); j++) glDeleteBuffers(1, &vaos.at(i).buffers.at(j));

		glDeleteVertexArrays(1, &vaos.at(i).vaoID);
	}

	vaos.clear();
}
