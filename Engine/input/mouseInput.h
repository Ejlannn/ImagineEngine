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

#ifndef _IE_MOUSE_INPUT_H_
#define _IE_MOUSE_INPUT_H_

#include "../platform/types.h"

enum MouseAxis
{
	X,
	Y
};

enum MouseButton
{
	BUTTON_LEFT = 0,
	BUTTON_RIGHT = 1,
	BUTTON_MIDDLE = 2
};

class Event;

class MouseInput
{
	friend class Event;

public:
	static S32 getMousePosition(MouseAxis axis);

	static bool isPressed(MouseButton button);
	static bool isReleased(MouseButton button);

	static void setRelativeMouseMode(bool state);
	static void setCursorVisibility(bool visibility);

private:
	static void init();
	static void update(U8 mouseButtonsState[3]);
	static void destroy();
};

#endif
