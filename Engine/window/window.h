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

#ifndef _IE_WINDOW_H_
#define _IE_WINDOW_H_

#include "../platform/types.h"

class Game;
class Event;
class GraphicsDevice;

class Window
{
	friend class Game;
	friend class Event;
	friend class GraphicsDevice;

public:
	static void setTitle(char *windowTitle);
	static void setWidth(U16 windowWidth);
	static void setHeight(U16 windowHeight);
	static void setPositionX(S16 positionX);
	static void setPositionY(S16 positionY);
	static void setFullscreen(bool windowFullscreen);
	static void setVisibility(bool windowVisibility);

	static char *getTitle();
	static U16 getWidth();
	static U16 getHeight();
	static S16 getPositionX();
	static S16 getPositionY();
	static bool getFullscreen();
	static bool getVisibility();

	static void cancelExiting();

	static bool isExiting();

private:
	static S16 create();
	static void firstUpdate();
	static void destroy();
	static void update();
	static void shouldExit();
};

#endif
