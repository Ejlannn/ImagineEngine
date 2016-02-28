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

#include "resourceLoader.h"

#include "../error/error.h"

TTF_Font *ResourceLoader::loadFont(FilePath *fontFile, U16 fontSize)
{
	fontFile->getFile().close();

	TTF_Font *font = TTF_OpenFont(fontFile->getPath().c_str(), fontSize);

	if(!font)
	{
		char *line1 = (char*) "Cannot load font file:\n";

		std::string msgTemp;
		msgTemp += line1;
		msgTemp += fontFile->getPath();

		char *message = &msgTemp[0u];

		Error::throwError(message);

		delete line1;
		delete message;
	}

	fontFile->reopen();

	return font;
}

SDL_Surface *ResourceLoader::loadImage(FilePath *imageFile)
{
	imageFile->getFile().close();

	SDL_Surface *surface = IMG_Load(imageFile->getPath().c_str());

	if(!surface)
	{
		char *line1 = (char*) "Cannot load image file:\n";

		std::string msgTemp;
		msgTemp += line1;
		msgTemp += imageFile->getPath();

		char *message = &msgTemp[0u];

		Error::throwError(message);

		delete line1;
		delete message;
	}

	imageFile->reopen();

	return surface;
}

Mix_Music *ResourceLoader::loadMusic(FilePath *musicFile)
{
	musicFile->getFile().close();

	Mix_Music *music = Mix_LoadMUS(musicFile->getPath().c_str());

	if(!music)
	{
		char *line1 = (char*) "Cannot load music file:\n";

		std::string msgTemp;
		msgTemp += line1;
		msgTemp += musicFile->getPath();

		char *message = &msgTemp[0u];

		Error::throwError(message);

		delete line1;
		delete message;
	}

	musicFile->reopen();

	return music;
}

Mix_Chunk *ResourceLoader::loadSound(FilePath *soundFile)
{
	soundFile->getFile().close();

	Mix_Chunk *sound = Mix_LoadWAV(soundFile->getPath().c_str());

	if(!sound)
	{
		char *line1 = (char*) "Cannot load sound file:\n";

		std::string msgTemp;
		msgTemp += line1;
		msgTemp += soundFile->getPath();

		char *message = &msgTemp[0u];

		Error::throwError(message);

		delete line1;
		delete message;
	}

	soundFile->reopen();

	return sound;
}
