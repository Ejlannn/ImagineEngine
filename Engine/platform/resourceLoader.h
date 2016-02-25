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

#ifndef _IE_RESOURCE_LOADER_H_
#define _IE_RESOURCE_LOADER_H_

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "file.h"
#include "types.h"

class Audio;
class SkyboxAsset;
class TextureAsset;
class GraphicsDevice;
class UITexture;
class UIText;

class ResourceLoader
{
	friend class Audio;
	friend class SkyboxAsset;
	friend class TextureAsset;
	friend class GraphicsDevice;
	friend class UITexture;
	friend class UIText;

	static TTF_Font *loadFont(FilePath *fontFile, U16 fontSize);
	static SDL_Surface *loadImage(FilePath *imageFile);
	static Mix_Music *loadMusic(FilePath *musicFile);
	static Mix_Chunk *loadSound(FilePath *soundFile);
};

#endif
