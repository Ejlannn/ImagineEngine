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
#include "../engine/game/game.h"
#include "../engine/script.h"
#include "../input/input.h"
#include "../math/math.h"
#include "../ui/console/console.h"
#include "../window/window.h"

#include <iostream>

static SDL_Event event;

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
		Scene *currentScene = Game::getCurrentScene();

		switch(event.type)
		{
		case SDL_QUIT:
			Window::shouldExit();
			break;
		case SDL_MOUSEBUTTONDOWN:
			if(event.button.button == SDL_BUTTON_LEFT) buttonsState[BUTTON_LEFT] = 1;
			else if(event.button.button == SDL_BUTTON_MIDDLE) buttonsState[BUTTON_MIDDLE] = 1;
			else if(event.button.button == SDL_BUTTON_RIGHT) buttonsState[BUTTON_RIGHT] = 1;

			if(currentScene == nullptr) break;

			if(currentScene->entities.size() > 0)
			{
				for(U16 i = 0; i < currentScene->entities.size(); i++)
				{
					if(currentScene->entities.at(i)->hasComponent("ScriptComponent"))
					{
						ScriptComponent *scriptComponent = (ScriptComponent*) currentScene->entities.at(i)->getComponent("ScriptComponent");

						if(scriptComponent->scripts.size() > 0)
						{
							for(U16 j = 0; j < scriptComponent->scripts.size(); j++)
							{
								MouseButton button;

								if(event.button.button == SDL_BUTTON_LEFT) button = MouseButton::BUTTON_LEFT;
								else if(event.button.button == SDL_BUTTON_MIDDLE) button = MouseButton::BUTTON_MIDDLE;
								else if(event.button.button == SDL_BUTTON_RIGHT) button = MouseButton::BUTTON_RIGHT;
								else break;

								scriptComponent->scripts.at(j)->onMouseButtonDown(button);
							}
						}
					}
				}
			}
			break;
		case SDL_KEYDOWN:
			if((KeyboardKey) event.key.keysym.scancode == KeyboardKey::KEY_GRAVE) Console::switchVis();
			if(!Console::isVisible())
			{
				Scene *currentScene = Game::getCurrentScene();

				if(currentScene == nullptr) break;

				if(currentScene->entities.size() > 0)
				{
					for(U16 i = 0; i < currentScene->entities.size(); i++)
					{
						if(currentScene->entities.at(i)->hasComponent("ScriptComponent"))
						{
							ScriptComponent *scriptComponent = (ScriptComponent*) currentScene->entities.at(i)->getComponent("ScriptComponent");

							if(scriptComponent->scripts.size() > 0)
							{
								for(U16 j = 0; j < scriptComponent->scripts.size(); j++)
								{
									scriptComponent->scripts.at(j)->onKeyboardKeyDown(KeyboardKey(event.key.keysym.scancode));
								}
							}
						}
					}
				}
			}
			else
			{
				static const U8 *keys = SDL_GetKeyboardState(nullptr);

				bool big = false;

				if(keys[KeyboardKey::KEY_LSHIFT] || keys[KeyboardKey::KEY_RSHIFT]) big = true;

				Console::onConsoleKeyDown(KeyboardKey(event.key.keysym.scancode), big);

				delete keys;
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
