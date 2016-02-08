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

class VertexArrayObject
{
	friend class ModelAsset;
	friend class Game;
	friend class SkyboxAsset;

private:
	static U32 loadToVAO(std::vector<F32> positions, S16 dimension);
	static U32 loadToVAO(std::vector<F32> vertices, std::vector<F32> normals, std::vector<U32> indices);
	static U32 loadToVAO(std::vector<F32> vertices, std::vector<F32> textureVectors, std::vector<F32> normals, std::vector<U32> indices);
	static void destroyAll();
};

#endif
