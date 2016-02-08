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

#include "time.h"

#include <SDL2/SDL_timer.h>

static	U64 previousTime = 0;
static	U64	currentTime = 0;
static	F32 deltaTime = 0.0f;
static	U64	elapsedTime = 0;

void Time::start()
{
	previousTime = SDL_GetTicks();
}

void Time::update()
{
	currentTime = SDL_GetTicks();

	deltaTime = (F32) currentTime - (F32) previousTime;
	elapsedTime += deltaTime;

	previousTime = currentTime;
}

F32 Time::getDeltaTime()
{
	return deltaTime;
}

U64 Time::getElapsedTime()
{
	return elapsedTime;
}
