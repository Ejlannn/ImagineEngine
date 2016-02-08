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

#include <string>
#include <SDL2/SDL_messagebox.h>
#include "../engine/game/game.h"

char *title = (char*) "Imagine Engine";

void showMessageBox(char *message)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, NULL);
}

void exitGame()
{
	Game::exit();
}

void Error::throwError(char *message)
{
	exitGame();
	showMessageBox(message);
}

void Error::throwErrorCode(S16 errorCode)
{
	exitGame();

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
}

void Error::throwErrorFileNotFound(char *path)
{
	exitGame();

	char *line1 = (char*) "File not found:\n"; //1st line
	//path = 2nd line

	std::string msgTemp;
	msgTemp += line1;
	msgTemp += path;

	char *message = &msgTemp[0u];

	showMessageBox(message);
}