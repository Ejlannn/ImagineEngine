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

#ifndef _IE_VERTEX_ARRAY_OBJECT_H_
#define _IE_VERTEX_ARRAY_OBJECT_H_

#include "../graphics/face.h"
#include "../math/math.h"
#include "../platform/types.h"

class ModelAsset;
class Game;
class SkyboxAsset;
class GraphicsDevice;

class VertexArrayObject
{
	friend class ModelAsset;
	friend class Game;
	friend class SkyboxAsset;
	friend class GraphicsDevice;

	static U32 loadToVAO(std::vector<F32> positions, S16 dimension);
	static U32 loadToVAO(std::vector<F32> positions, std::vector<F32> textureVectors);
	static U32 loadToVAO(std::vector<F32> vertices, std::vector<F32> normals, std::vector<U64> indices);
	static U32 loadToVAO(std::vector<F32> vertices, std::vector<F32> textureVectors, std::vector<F32> normals, std::vector<U64> indices);
	static void destroy(U32 vao);
	static void destroyAll();
	static U32 createVAO();
	static U32 storeF32(U32 attributeNumber, U16 size, std::vector<F32> data);
	static U32 storeIndices(std::vector<U64> data);
};

#endif
