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

#ifndef _IE_SPRITE_ASSET_H_
#define _IE_SPRITE_ASSET_H_

#include <string>
#include "../texture/textureAsset.h"
#include "../../math/math.h"
#include "../../platform/file.h"
#include "../../platform/types.h"
#include "../../time/timer.h"

class Scene;
class GraphicsDevice;

/******************************
 * SpriteLayer
 *****************************/
class SpriteAsset;

class SpriteLayer
{
	friend class SpriteAsset;
	friend class Scene;
	friend class GraphicsDevice;

public:
	void addTexture(TextureAsset *texture);
	void setInterval(U32 ms);

	std::string getName();

private:
	SpriteLayer(std::string name);

	~SpriteLayer();

	std::string name;
	U32 interval;
	U32 currentTexturePointer;
	std::vector<TextureAsset*> textures;
	Timer *timer;

	void start();
	void stop();
	void update();
};

/******************************
 * SpriteAsset
 *****************************/
class SpriteAsset
{
	friend class Scene;
	friend class GraphicsDevice;

public:
	SpriteAsset();

	~SpriteAsset();

	SpriteLayer *createLayer(std::string layerName);
	void removeLayer(std::string layerName);
	void setCurrentLayer(std::string layerName);

private:
	SpriteLayer *currentLayer;
	std::vector<SpriteLayer*> layers;
};

#endif
