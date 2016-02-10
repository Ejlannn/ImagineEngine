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

#include <SDL2/SDL_image.h>
#include "../../error/error.h"
#include "../../graphics/vertexArrayObject.h"

S32 vertexCount = 0;

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

	std::vector<F32> positions;

	positions.push_back(-size);
	positions.push_back(size);
	positions.push_back(-size);
	positions.push_back(-size);
	positions.push_back(-size);
	positions.push_back(-size);
	positions.push_back(size);
	positions.push_back(-size);
	positions.push_back(-size);
	positions.push_back(size);
	positions.push_back(-size);
	positions.push_back(-size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(-size);
	positions.push_back(-size);
	positions.push_back(size);
	positions.push_back(-size);

	positions.push_back(-size);
	positions.push_back(-size);
	positions.push_back(size);
	positions.push_back(-size);
	positions.push_back(-size);
	positions.push_back(-size);
	positions.push_back(-size);
	positions.push_back(size);
	positions.push_back(-size);
	positions.push_back(-size);
	positions.push_back(size);
	positions.push_back(-size);
	positions.push_back(-size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(-size);
	positions.push_back(-size);
	positions.push_back(size);

	positions.push_back(size);
	positions.push_back(-size);
	positions.push_back(-size);
	positions.push_back(size);
	positions.push_back(-size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(-size);
	positions.push_back(size);
	positions.push_back(-size);
	positions.push_back(-size);

	positions.push_back(-size);
	positions.push_back(-size);
	positions.push_back(size);
	positions.push_back(-size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(-size);
	positions.push_back(size);
	positions.push_back(-size);
	positions.push_back(-size);
	positions.push_back(size);

	positions.push_back(-size);
	positions.push_back(size);
	positions.push_back(-size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(-size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(-size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(-size);
	positions.push_back(size);
	positions.push_back(-size);

	positions.push_back(-size);
	positions.push_back(-size);
	positions.push_back(-size);
	positions.push_back(-size);
	positions.push_back(-size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(-size);
	positions.push_back(-size);
	positions.push_back(size);
	positions.push_back(-size);
	positions.push_back(-size);
	positions.push_back(-size);
	positions.push_back(-size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(-size);
	positions.push_back(size);

	vertexCount = positions.size() / 3;

	vaoID = VertexArrayObject::loadToVAO(positions, 3);

	surface[0] = IMG_Load(path[0]->getPath().c_str());
	surface[1] = IMG_Load(path[1]->getPath().c_str());
	surface[2] = IMG_Load(path[2]->getPath().c_str());
	surface[3] = IMG_Load(path[3]->getPath().c_str());
	surface[4] = IMG_Load(path[4]->getPath().c_str());
	surface[5] = IMG_Load(path[5]->getPath().c_str());

	for(S16 i = 0; i < 6; i++)
	{
		if(!surface[i]) Error::throwError((char*) "Cannot load image file!");
	}
}

SkyboxAsset::~SkyboxAsset()
{
	for(U16 i = 0; i < 6; i++)
	{
		delete path[i];
	}

	delete &id;
	delete &vaoID;

	for(U16 i = 0; i < 6; i++)
	{
		SDL_FreeSurface(surface[i]);
	}
}

S32 SkyboxAsset::getVertexCount()
{
	return vertexCount;
}
