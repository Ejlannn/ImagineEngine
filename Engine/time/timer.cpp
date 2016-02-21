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

#include "timer.h"

#include <SDL2/SDL_timer.h>

Timer::Timer()
{
	previousTime = 0;
	elapsedTime = 0;
}

Timer::~Timer() {}

void Timer::start()
{
	elapsedTime = 0;
	previousTime = SDL_GetTicks();
}

void Timer::stop()
{
	previousTime = 0;
	elapsedTime = (SDL_GetTicks() - previousTime) / 1000;
}

void Timer::reset()
{
	elapsedTime = 0;
	previousTime = 0;
}

U32 Timer::getElapsedTime()
{
	if(previousTime == 0) return elapsedTime;

	return (U32) (SDL_GetTicks() - previousTime) / 1000;
}
