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

#include "spriteAsset.h"

/******************************
 * SpriteLayer
 *****************************/
SpriteLayer::SpriteLayer(std::string name)
{
	this->name = name;
	interval = 100;
	currentTexturePointer = 0;
	timer = new Timer();
}

SpriteLayer::~SpriteLayer()
{
	delete timer;

	textures.clear();
}

void SpriteLayer::addTexture(TextureAsset *texture)
{
	if(texture == nullptr)
	{
		return;
	}

	textures.push_back(texture);
}

void SpriteLayer::setInterval(U32 ms)
{
	interval = ms;
}

std::string SpriteLayer::getName()
{
	return name;
}

void SpriteLayer::start()
{
	timer->start();
}

void SpriteLayer::stop()
{
	timer->stop();
}

void SpriteLayer::update()
{
	if(textures.size() == 1)
	{
		currentTexturePointer = 0;
		timer->reset();
		return;
	}

	if(timer->getElapsedTime() >= interval)
	{
		U16 changes = timer->getElapsedTime() / interval;

		if(changes == 1)
		{
			if(currentTexturePointer + 2 > textures.size()) currentTexturePointer = 0;
			else currentTexturePointer++;
		}
		else
		{
			for(U16 i = 0; i < changes; i++)
			{
				if(currentTexturePointer + 2 > textures.size()) currentTexturePointer = 0;
				else currentTexturePointer++;
			}
		}

		timer->reset();
	}
}

/******************************
 * SpriteAsset
 *****************************/
SpriteAsset::SpriteAsset()
{
	currentLayer = nullptr;
}

SpriteAsset::~SpriteAsset()
{
	if(layers.size() != 0)
	{
		for(U16 i = 0; i < layers.size(); i++)
		{
			delete layers.at(i);
		}
	}

	layers.clear();
}

SpriteLayer *SpriteAsset::createLayer(std::string layerName)
{
	for(U16 i = 0; i < layers.size(); i++)
	{
		if(layers.at(i)->name == layerName) return nullptr;
	}

	SpriteLayer *layer = new SpriteLayer(layerName);

	layers.push_back(layer);

	return layer;
}

void SpriteAsset::removeLayer(std::string layerName)
{
	for(U16 i = 0; i < layers.size(); i++)
	{
		if(layers.at(i)->name == layerName)
		{
			layers.erase(layers.begin() + i);
			return;
		}
	}

	//If not exist
}

void SpriteAsset::setCurrentLayer(std::string layerName)
{
	for(U16 i = 0; i < layers.size(); i++)
	{
		if(layers.at(i)->name == layerName)
		{
			if(currentLayer != nullptr) currentLayer->stop();
			currentLayer = layers.at(i);
			currentLayer->start();
			return;
		}
	}

	//If not exist
}
