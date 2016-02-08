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

#include "event.h"

#include <SDL2/SDL_events.h>
#include "../input/input.h"
#include "../window/window.h"

static SDL_Event event; //Handles events

void Event::init()
{
	MouseInput::init();
}

void Event::update()
{
	SDL_PumpEvents();

	U8 buttonsState[3] {0, 0, 0};

	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT:
			Window::shouldExit();
			break;
		case SDL_MOUSEBUTTONDOWN:
			if(event.button.button == SDL_BUTTON_LEFT) buttonsState[BUTTON_LEFT] = 1;
			else if(event.button.button == SDL_BUTTON_MIDDLE) buttonsState[BUTTON_MIDDLE] = 1;
			else if(event.button.button == SDL_BUTTON_RIGHT) buttonsState[BUTTON_RIGHT] = 1;
			break;
		}
	}

	KeyboardInput::update();
	MouseInput::update(buttonsState);
}

void Event::destroy()
{
	KeyboardInput::destroy();
	MouseInput::destroy();
}
