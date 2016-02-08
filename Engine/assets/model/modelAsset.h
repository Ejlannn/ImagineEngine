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

#ifndef _IE_MODEL_ASSET_H_
#define _IE_MODEL_ASSET_H_

#include "../../math/math.h"
#include "../../graphics/face.h"

class ModelLoader;
class GraphicsDevice;
class Terrain;

class ModelAsset
{
	friend class ModelLoader;
	friend class GraphicsDevice;
	friend class Terrain;

public:
	U32 getVertexCount();

private:
	ModelAsset();

	U32 vaoID;
	U32 vertexCount;

	std::vector<Vector3*> vertices;
	std::vector<Vector3*> normalVectors;
	std::vector<Vector2*> textureVectors;
	std::vector<Face*> faces;

	void load();
};

#endif