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

#include "mouseInput.h"

#include <SDL2/SDL_mouse.h>

U8		buttonsState[3] = {0, 0, 0};
S32		x = 0;
S32		y = 0;

void MouseInput::init()
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void MouseInput::update(U8 mouseButtonsState[3])
{
	buttonsState[0] = mouseButtonsState[0];
	buttonsState[1] = mouseButtonsState[1];
	buttonsState[2] = mouseButtonsState[2];

	S32 tempX, tempY;

	if(SDL_GetRelativeMouseMode() == SDL_TRUE)
	{

		SDL_GetRelativeMouseState(&tempX, &tempY);

		x += tempX;
		y += tempY;
	}
	else
	{
		SDL_GetMouseState(&tempX, &tempY);

		x = tempX;
		y = tempY;
	}
}

void MouseInput::destroy()
{
	for(S16 i = 1; i < 4; i++)
	{
		delete &buttonsState[i];
	}

	delete &x;
	delete &y;
}

S32 MouseInput::getMousePosition(MouseAxis axis)
{
	if(axis == MouseAxis::X) return x;
	else if(axis == MouseAxis::Y) return y;

	return 0;
}

bool MouseInput::isPressed(MouseButton button)
{
	if(buttonsState[button] == 1) return true;

	return false;
}

bool MouseInput::isReleased(MouseButton button)
{
	if(!isPressed(button)) return true;

	return false;
}

void MouseInput::setRelativeMouseMode(bool state)
{
	if(state == true) SDL_SetRelativeMouseMode(SDL_TRUE);
	else SDL_SetRelativeMouseMode(SDL_FALSE);
}
