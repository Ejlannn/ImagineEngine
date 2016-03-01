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

#include "text.h"

#include "uiElementsHandler.h"
#include "../error/error.h"
#include "../graphics/graphicsDevice.h"
#include "../platform/resourceLoader.h"

SDL_Surface *UIText::getTextSurface(std::string message, FilePath *fontFile, U16 size, Color3 color)
{
	SDL_Color txtColor = { (U8)color.r, (U8)color.g, (U8)color.b };

	fontFile->getFile().close();

	TTF_Font *font = ResourceLoader::loadFont(fontFile, size);

	fontFile->reopen();

	if(!font) Error::throwError((char*) "Cannot load font file!");

	SDL_Surface *fontSurface = TTF_RenderText_Blended(font, message.c_str(), txtColor);

	return fontSurface;
}

UIText::UIText(std::string message, FilePath *fontFile, Vector2 position, U16 size)
{
	this->message = message;
	this->fontFile = fontFile;
	this->position = position;
	this->size = size;
	color.r = color.g = color.b = 1.0f;

	SDL_Surface *surface = getTextSurface(message, fontFile, size, color);

	element.position = position;
	element.surface = surface;

	UIElementsHandler::addUIElement(element);
}

UIText::UIText(std::string message, FilePath *fontFile, Vector2 position, U16 size, Color3 color)
{
	this->message = message;
	this->fontFile = fontFile;
	this->position = position;
	this->size = size;
	this->color = color;

	SDL_Surface *surface = getTextSurface(message, fontFile, size, color);

	element.position = position;
	element.surface = surface;

	UIElementsHandler::addUIElement(element);
}

UIText::~UIText()
{
	UIElementsHandler::removeUIElement(element);

	SDL_FreeSurface(element.surface);
}

void UIText::changeMessage(std::string newMessage)
{
	message = newMessage;

	recreate();
}

void UIText::changeFontFile(FilePath *newFontFile)
{
	fontFile = newFontFile;

	recreate();
}

void UIText::changePosition(Vector2 newPosition)
{
	position = newPosition;

	recreate();
}

void UIText::changeSize(U16 newSize)
{
	size = newSize;

	recreate();
}

void UIText::changeTextColor(Color3 newColor)
{
	color = newColor;

	recreate();
}

void UIText::renderSimpleText(const std::string &message, FilePath *fontFile, U16 size, Vector2 position)
{
	GraphicsDevice::addTextToRender(message, fontFile, size, position);
}

void UIText::renderSimpleText(const std::string &message, FilePath *fontFile, U16 size, Vector2 position, Color3 color)
{
	GraphicsDevice::addTextToRender(message, fontFile, size, position, color);
}

void UIText::recreate()
{
	SDL_Surface *surface;

	UIElementsHandler::removeUIElement(element);

	element.position = position;
	element.surface = surface;

	UIElementsHandler::addUIElement(element);
}
