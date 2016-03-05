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

#include <cmath>
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

	std::vector<Vector3*> verticesConverted;
	std::vector<Vector2*> texturesConverted;
	std::vector<Vector3*> normalsConverted;

	for(U64 i = 0; i < faces.size(); i++)
	{
		indices.push_back(i * 3);
		indices.push_back(i * 3 + 1);
		indices.push_back(i * 3 + 2);

		verticesConverted.push_back(vertices.at(faces.at(i)->v1 - 1));
		verticesConverted.push_back(vertices.at(faces.at(i)->v2 - 1));
		verticesConverted.push_back(vertices.at(faces.at(i)->v3 - 1));

		if(textureVectors.size() > 0)
		{
			texturesConverted.push_back(textureVectors.at(faces.at(i)->vt1 - 1));
			texturesConverted.push_back(textureVectors.at(faces.at(i)->vt2 - 1));
			texturesConverted.push_back(textureVectors.at(faces.at(i)->vt3 - 1));
		}

		if(normalVectors.size() > 0)
		{
			normalsConverted.push_back(normalVectors.at(faces.at(i)->vn1 - 1));
			normalsConverted.push_back(normalVectors.at(faces.at(i)->vn2 - 1));
			normalsConverted.push_back(normalVectors.at(faces.at(i)->vn3 - 1));
		}
		else
		{
			//TODO: Generate
		}
	}

	for(U64 i = 0; i < verticesConverted.size(); i++)
	{
		verts.push_back(verticesConverted.at(i)->x);
		verts.push_back(verticesConverted.at(i)->y);
		verts.push_back(verticesConverted.at(i)->z);
	}

	if(texturesConverted.size() > 0)
	{
		for(U64 i = 0; i < texturesConverted.size(); i++)
		{
			texts.push_back(texturesConverted.at(i)->x);
			texts.push_back(1.0f - texturesConverted.at(i)->y);
		}
	}

	if(normalsConverted.size() > 0)
	{
		for(U64 i = 0; i < normalsConverted.size(); i++)
		{
			norms.push_back(normalsConverted.at(i)->x);
			norms.push_back(normalsConverted.at(i)->y);
			norms.push_back(normalsConverted.at(i)->z);
		}
	}

	vertexCount = indices.size();

	if(texts.size() == 0) vaoID = VertexArrayObject::loadToVAO(verts, norms, indices);
	else vaoID = VertexArrayObject::loadToVAO(verts, texts, norms, indices);
}

U64 ModelAsset::getVertexCount()
{
	return vertexCount;
}
