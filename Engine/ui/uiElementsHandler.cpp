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

#include "uiElementsHandler.h"

static std::vector<UIElement> elements;
static U64 elementCounter = 0;

UIElement::UIElement()
{
	surface = nullptr;

	elementID = elementCounter;
	elementCounter++;
}

UIElement::UIElement(Vector2 position, SDL_Surface *surface)
{
	this->position = position;
	this->surface = surface;

	elementID = elementCounter;
	elementCounter++;
}

UIElement::~UIElement() {}

void UIElementsHandler::addUIElement(UIElement element)
{
	elements.push_back(element);
}

void UIElementsHandler::removeUIElement(UIElement element)
{
	for(U16 i = 0; i < elements.size(); i++)
	{
		if(elements.at(i).elementID == element.elementID)
		{
			if(elements.at(i).surface) SDL_FreeSurface(elements.at(i).surface);

			elements.erase(elements.begin() + i);
		}
	}
}

std::vector<UIElement> UIElementsHandler::getElements()
{
	return elements;
}
