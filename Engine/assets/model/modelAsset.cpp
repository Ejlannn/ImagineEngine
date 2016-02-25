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

#include "modelAsset.h"

#include <iostream> //testing
#include <cmath>
#include <cstdlib>
#include "../../error/error.h"
#include "../../graphics/vertexArrayObject.h"

ModelAsset::ModelAsset()
{
	vaoID = 0;
	vertexCount = 0;
}

ModelAsset::~ModelAsset()
{
	vertices.clear();
	normalVectors.clear();
	textureVectors.clear();
	faces.clear();
}

void ModelAsset::load()
{
	std::vector<U64> indices;

	std::vector<F32> verts;
	std::vector<F32> texts;
	std::vector<F32> norms;

	for(U64 i = 0; i < faces.size(); i++)
	{
	    indices.push_back(U64(faces.at(i)->v1 - 1));
	    indices.push_back(U64(faces.at(i)->v2 - 1));
	    indices.push_back(U64(faces.at(i)->v3 - 1));
	}

	vertexCount = indices.size();

	for(U64 i = 0; i < vertices.size(); i++)
	{
	    verts.push_back(vertices.at(i)->x);
	    verts.push_back(vertices.at(i)->y);
	    verts.push_back(vertices.at(i)->z);
	}

	F32 textureArray[faces.size() * 2 * 3];

    if(textureVectors.size() > 0)
    {
		for(U64 i = 0; i < faces.size(); i++)
		{
			for(U16 j = 0; j < 3; j++)
			{
				U32 currentVertexPointer = 0;

				if(j == 0) currentVertexPointer = faces.at(i)->v1 - 1;
				else if(j == 1) currentVertexPointer = faces.at(i)->v2 - 1;
				else if(j == 2) currentVertexPointer = faces.at(i)->v3 - 1;

				Vector2 *currentTexture = nullptr;

				if(j == 0) currentTexture = textureVectors.at(faces.at(i)->vt1 - 1);
				else if(j == 1) currentTexture = textureVectors.at(faces.at(i)->vt2 - 1);
				else if(j == 2) currentTexture = textureVectors.at(faces.at(i)->vt3 - 1);

				textureArray[currentVertexPointer * 2] = currentTexture->x;
				textureArray[currentVertexPointer * 2 + 1] = (1.0f - currentTexture->y);
			}
		}

		for(U64 i = 0; i < faces.size() * 2 * 3; i++)
		{
			texts.push_back(textureArray[i]);
		}
    }

    if(normalVectors.size() == 0)
    {
    	//TODO: Generate normals
    }

    F32 normalArray[faces.size() * 3 * 3];

    if(normalVectors.size() > 0)
    {
		for(U64 i = 0; i < faces.size(); i++)
		{
			for(U16 j = 0; j < 3; j++)
			{
				U64 currentVertexPointer = 0;

				if(j == 0) currentVertexPointer = faces.at(i)->v1 - 1;
				else if(j == 1) currentVertexPointer = faces.at(i)->v2 - 1;
				else if(j == 2) currentVertexPointer = faces.at(i)->v3 - 1;

				Vector3 *currentNormal = nullptr;

				if(j == 0) currentNormal = normalVectors.at(faces.at(i)->vn1 - 1);
				else if(j == 1) currentNormal = normalVectors.at(faces.at(i)->vn2 - 1);
				else if(j == 2) currentNormal = normalVectors.at(faces.at(i)->vn3 - 1);

				normalArray[currentVertexPointer * 2] = currentNormal->x;
				normalArray[currentVertexPointer * 2 + 1] = currentNormal->y;
				normalArray[currentVertexPointer * 2 + 2] = currentNormal->z;
			}
		}

		for(U64 i = 0; i < faces.size() * 3 * 3; i++)
		{
			norms.push_back(normalArray[i]);
		}
    }

	if(texts.size() == 0) vaoID = VertexArrayObject::loadToVAO(verts, norms, indices);
	else vaoID = VertexArrayObject::loadToVAO(verts, texts, norms, indices);
}

U64 ModelAsset::getVertexCount()
{
	return vertexCount;
}
