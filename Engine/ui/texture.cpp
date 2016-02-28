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

#include "texture.h"

#include "uiElementsHandler.h"
#include "../error/error.h"
#include "../platform/resourceLoader.h"

SDL_Surface *UITexture::getTextureSurface(FilePath *texturePath)
{
	texturePath->getFile().close();

	SDL_Surface *surface = ResourceLoader::loadImage(texturePath);

	texturePath->reopen();

	if(!surface) Error::throwError((char*) "Couldn't load img!");

	return surface;
}

UITexture::UITexture(FilePath *texturePath, Vector2 *position)
{
	this->texturePath = texturePath;
	this->position = position;

	SDL_Surface *surface = getTextureSurface(texturePath);

	element.position = position;
	element.surface = surface;

	UIElementsHandler::addUIElement(element);
}


UITexture::~UITexture()
{
	UIElementsHandler::removeUIElement(element);

	SDL_FreeSurface(element.surface);
}
