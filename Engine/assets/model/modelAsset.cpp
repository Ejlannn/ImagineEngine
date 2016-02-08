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

void ModelAsset::load()
{
	std::vector<U32> indices;

	std::vector<F32> verts;
	std::vector<F32> texts;
	std::vector<F32> norms;

	for(U32 i = 0; i < faces.size(); i++)
	{
	    indices.push_back(U32(faces.at(i)->v1 - 1));
	    indices.push_back(U32(faces.at(i)->v2 - 1));
	    indices.push_back(U32(faces.at(i)->v3 - 1));
	}

	vertexCount = indices.size();

	for(U32 i = 0; i < vertices.size(); i++)
	{
	    verts.push_back(vertices.at(i)->x);
	    verts.push_back(vertices.at(i)->y);
	    verts.push_back(vertices.at(i)->z);
	}

	F32 textureArray[faces.size() * 2 * 3];

    if(textureVectors.size() > 0)
    {
		for(U32 i = 0; i < faces.size(); i++)
		{
			for(U32 j = 0; j < 3; j++)
			{
				U32 currentVertexPointer = 0;

				if(j == 0) currentVertexPointer = faces.at(i)->v1 - 1;
				else if(j == 1) currentVertexPointer = faces.at(i)->v2 - 1;
				else if(j == 2) currentVertexPointer = faces.at(i)->v3 - 1;

				Vector2 *currentTexture = NULL;

				if(j == 0) currentTexture = textureVectors.at(faces.at(i)->vt1 - 1);
				else if(j == 1) currentTexture = textureVectors.at(faces.at(i)->vt2 - 1);
				else if(j == 2) currentTexture = textureVectors.at(faces.at(i)->vt3 - 1);

				//texts.push_back(1.0f);
				//texts.push_back(0.0f);

				textureArray[currentVertexPointer * 2] = currentTexture->x;
				textureArray[currentVertexPointer * 2 + 1] = (1.0f - currentTexture->y);

				//texts.insert(texts.begin() + (currentVertexPointer * 2) - 1, currentTexture->x);
				//texts.insert(texts.begin() + (currentVertexPointer * 2 + 1) - 1, currentTexture->y);
			}
		}

		for(U32 i = 0; i < faces.size() * 2 * 3; i++)
		{
			//if(textureArray[i] > 1.0f || textureArray[i] < 0.0f) textureArray[i] = 0.0f;

			texts.push_back(textureArray[i]);
		}
    }

    F32 normalArray[faces.size() * 3 * 3];

    if(normalVectors.size() == 0)
    {
    	//TODO: Generate normals
    }

    if(normalVectors.size() > 0)
    {
		for(U32 i = 0; i < faces.size(); i++)
		{
			for(U32 j = 0; j < 3; j++)
			{
				U32 currentVertexPointer = 0;

				if(j == 0) currentVertexPointer = faces.at(i)->v1 - 1;
				else if(j == 1) currentVertexPointer = faces.at(i)->v2 - 1;
				else if(j == 2) currentVertexPointer = faces.at(i)->v3 - 1;

				Vector3 *currentNormal = normalVectors.at(faces.at(i)->vn - 1);

				normalArray[currentVertexPointer * 2] = currentNormal->x;
				normalArray[currentVertexPointer * 2 + 1] = 1.0f - currentNormal->y;
			}
		}

		for(U32 i = 0; i < faces.size() * 3 * 3; i++)
		{
			if(normalArray[i] > 1.0f || normalArray[i] < 0.0f) normalArray[i] = 0.0f;

			norms.push_back(normalArray[i]);
		}
    }

	if(texts.size() == 0) vaoID = VertexArrayObject::loadToVAO(verts, norms, indices);
	else vaoID = VertexArrayObject::loadToVAO(verts, texts, norms, indices);
}

U32 ModelAsset::getVertexCount()
{
	return vertexCount;
}
