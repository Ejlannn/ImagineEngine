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

#ifndef _IE_TEXT_H_
#define _IE_TEXT_H_

#include "uiElementsHandler.h"
#include "../math/math.h"
#include "../platform/file.h"

class UIElement;
class SDL_Surface;

class UIText
{
public:
	UIText(std::string message, FilePath *fontFile, Vector2 *position, U16 size);
	UIText(std::string message, FilePath *fontFile, Vector2 *position, U16 size, Color3 *color);

	~UIText();

	void changeMessage(std::string newMessage);
	void changeFontFile(FilePath *newFontFile);
	void changePosition(Vector2 *newPosition);
	void changeSize(U16 newSize);
	void changeTextColor(Color3 *newColor);

	static void renderSimpleText(const std::string &message, FilePath *fontFile, U16 size, Vector2 *position);

private:
	std::string message;
	FilePath *fontFile;
	Vector2 *position;
	U16 size;
	Color3 *color;
	UIElement element;

	static SDL_Surface *getTextSurface(std::string message, FilePath *fontFile, U16 size, Color3 *color);

	void recreate();
};

#endif
