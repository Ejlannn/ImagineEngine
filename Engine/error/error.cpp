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

#include "error.h"

#include <SDL2/SDL_messagebox.h>
#include "../engine/game/game.h"

static char *title = (char*) "Imagine Engine";

void Error::showMessageBox(char *message)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, nullptr);
}

void Error::throwError(char *message)
{
	showMessageBox(message);
	Game::exit();
}

void Error::throwErrorCode(S16 errorCode)
{
	switch(errorCode)
	{
	case 1:
		showMessageBox((char*) "Error 1: Failed to initialize SDL2 library");
		break;
	case 2:
		showMessageBox((char*) "Error 2: Failed to initialize GLEW library");
		break;
	case 3:
		showMessageBox((char*) "Error 3: Failed to create game window");
		break;
	case 4:
		showMessageBox((char*) "Error 4: Cannot compile shader");
		break;
	default:
		return;
	}

	Game::exit();
}
