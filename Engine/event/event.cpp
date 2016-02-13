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
#include "../math/math.h"
#include "../ui/console/console.h"
#include "../window/window.h"

#include <iostream>

static SDL_Event				event; //Handles events
std::vector <EventHandler*> 	eventHandlers;

void Event::registerEventHandler(EventHandler *eventHandler)
{
	for(U16 i = 0; i < eventHandlers.size(); i++)
	{
		if(eventHandlers.at(i) == eventHandler) return;
	}

	eventHandlers.push_back(eventHandler);
}

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
		case SDL_KEYDOWN:
			if(event.key.keysym.scancode == KeyboardKey::KEY_GRAVE) Console::switchVis();
			if(!Console::isVisible())
			{
				for(U16 i = 0; i < eventHandlers.size(); i++)
				{
					eventHandlers.at(i)->onKeyboardKeyDown(KeyboardKey(event.key.keysym.scancode));
				}
			}
			else
			{
				static const U8 *keys = SDL_GetKeyboardState(NULL);

				bool big = false;

				if(keys[KeyboardKey::KEY_LSHIFT] || keys[KeyboardKey::KEY_RSHIFT]) big = true;

				Console::onConsoleKeyDown(KeyboardKey(event.key.keysym.scancode), big);
			}
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
