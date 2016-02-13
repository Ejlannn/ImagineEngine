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

#include "keyboardInput.h"

#include <SDL2/SDL_keyboard.h>
#include "../ui/console/console.h"

static const U8 *keys; //Handles keyboard keys state

void KeyboardInput::update()
{
	keys = SDL_GetKeyboardState(NULL);
}

void KeyboardInput::destroy()
{
	delete keys;
}

bool KeyboardInput::isPressed(KeyboardKey key)
{
	if(Console::isVisible()) return false;

	if(keys[key]) return true;

	return false;
}

bool KeyboardInput::isReleased(KeyboardKey key)
{
	if(Console::isVisible()) return true;

	if(!isPressed(key)) return true;

	return false;
}
