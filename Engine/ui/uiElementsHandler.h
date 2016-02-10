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

#ifndef _IE_UI_ELEMENTS_HANDLER_H_
#define _IE_UI_ELEMENTS_HANDLER_H_

#include <string>
#include <SDL2/SDL_surface.h>
#include "../math/math.h"

class UIText;
class UITexture;
class GraphicsDevice;
class SDL_Surface;

class UIElementsHandler;

class UIElement
{
	friend class UIElementsHandler;
	friend class UIText;
	friend class UITexture;
	friend class GraphicsDevice;

private:
	UIElement(Vector2 *pos, SDL_Surface *surf)
	{
		position = pos;
		surface = surf;
		//type = typ;
	}

	~UIElement()
	{
		delete &position;

		SDL_FreeSurface(surface);

		delete &surface;
	}

	Vector2 	*position;
	SDL_Surface *surface;
	//std::string type;
};

class UIElementsHandler
{
	friend class UIText;
	friend class UITexture;
	friend class GraphicsDevice;

private:
	static void addUIElement(UIElement *element);
	static void removeUIElement(UIElement *element);

	static std::vector<UIElement*> getElements();
};

#endif
