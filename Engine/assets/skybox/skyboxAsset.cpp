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

#include "skyboxAsset.h"

#include "../../error/error.h"
#include "../../graphics/vertexArrayObject.h"
#include "../../platform/resourceLoader.h"

static S32 vertexCount = 0;

SkyboxAsset::SkyboxAsset(FilePath *path[6])
{
	float size = 500.0f;

	this->path[0] = path[0];
	this->path[1] = path[1];
	this->path[2] = path[2];
	this->path[3] = path[3];
	this->path[4] = path[4];
	this->path[5] = path[5];

	id = 0;

	std::vector<F32> positions1;
	std::vector<F32> positions2;
	std::vector<F32> positions3;
	std::vector<F32> positions4;
	std::vector<F32> positions5;
	std::vector<F32> positions6;

	positions1.push_back(-size);
	positions1.push_back(size);
	positions1.push_back(-size);
	positions1.push_back(-size);
	positions1.push_back(-size);
	positions1.push_back(-size);
	positions1.push_back(size);
	positions1.push_back(-size);
	positions1.push_back(-size);
	positions1.push_back(size);
	positions1.push_back(-size);
	positions1.push_back(-size);
	positions1.push_back(size);
	positions1.push_back(size);
	positions1.push_back(-size);
	positions1.push_back(-size);
	positions1.push_back(size);
	positions1.push_back(-size);

	positions2.push_back(-size);
	positions2.push_back(-size);
	positions2.push_back(size);
	positions2.push_back(-size);
	positions2.push_back(-size);
	positions2.push_back(-size);
	positions2.push_back(-size);
	positions2.push_back(size);
	positions2.push_back(-size);
	positions2.push_back(-size);
	positions2.push_back(size);
	positions2.push_back(-size);
	positions2.push_back(-size);
	positions2.push_back(size);
	positions2.push_back(size);
	positions2.push_back(-size);
	positions2.push_back(-size);
	positions2.push_back(size);

	positions3.push_back(size);
	positions3.push_back(-size);
	positions3.push_back(-size);
	positions3.push_back(size);
	positions3.push_back(-size);
	positions3.push_back(size);
	positions3.push_back(size);
	positions3.push_back(size);
	positions3.push_back(size);
	positions3.push_back(size);
	positions3.push_back(size);
	positions3.push_back(size);
	positions3.push_back(size);
	positions3.push_back(size);
	positions3.push_back(-size);
	positions3.push_back(size);
	positions3.push_back(-size);
	positions3.push_back(-size);

	positions4.push_back(-size);
	positions4.push_back(-size);
	positions4.push_back(size);
	positions4.push_back(-size);
	positions4.push_back(size);
	positions4.push_back(size);
	positions4.push_back(size);
	positions4.push_back(size);
	positions4.push_back(size);
	positions4.push_back(size);
	positions4.push_back(size);
	positions4.push_back(size);
	positions4.push_back(size);
	positions4.push_back(-size);
	positions4.push_back(size);
	positions4.push_back(-size);
	positions4.push_back(-size);
	positions4.push_back(size);

	positions5.push_back(-size);
	positions5.push_back(size);
	positions5.push_back(-size);
	positions5.push_back(size);
	positions5.push_back(size);
	positions5.push_back(-size);
	positions5.push_back(size);
	positions5.push_back(size);
	positions5.push_back(size);
	positions5.push_back(size);
	positions5.push_back(size);
	positions5.push_back(size);
	positions5.push_back(-size);
	positions5.push_back(size);
	positions5.push_back(size);
	positions5.push_back(-size);
	positions5.push_back(size);
	positions5.push_back(-size);

	positions6.push_back(-size);
	positions6.push_back(-size);
	positions6.push_back(-size);
	positions6.push_back(-size);
	positions6.push_back(-size);
	positions6.push_back(size);
	positions6.push_back(size);
	positions6.push_back(-size);
	positions6.push_back(-size);
	positions6.push_back(size);
	positions6.push_back(-size);
	positions6.push_back(-size);
	positions6.push_back(-size);
	positions6.push_back(-size);
	positions6.push_back(size);
	positions6.push_back(size);
	positions6.push_back(-size);
	positions6.push_back(size);

	vertexCount = positions1.size() / 3;

	vaoID[0] = VertexArrayObject::loadToVAO(positions1, 3);
	vaoID[1] = VertexArrayObject::loadToVAO(positions2, 3);
	vaoID[2] = VertexArrayObject::loadToVAO(positions3, 3);
	vaoID[3] = VertexArrayObject::loadToVAO(positions4, 3);
	vaoID[4] = VertexArrayObject::loadToVAO(positions5, 3);
	vaoID[5] = VertexArrayObject::loadToVAO(positions6, 3);

	surface[0] = ResourceLoader::loadImage(path[0]);
	surface[1] = ResourceLoader::loadImage(path[1]);
	surface[2] = ResourceLoader::loadImage(path[2]);
	surface[3] = ResourceLoader::loadImage(path[3]);
	surface[4] = ResourceLoader::loadImage(path[4]);
	surface[5] = ResourceLoader::loadImage(path[5]);
}

SkyboxAsset::~SkyboxAsset()
{
	for(U16 i = 0; i < 6; i++)
	{
		VertexArrayObject::destroy(vaoID[i]);
		SDL_FreeSurface(surface[i]);
	}
}

S32 SkyboxAsset::getVertexCount()
{
	return vertexCount;
}
