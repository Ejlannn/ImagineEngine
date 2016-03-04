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

#include "window.h"

#include <SDL2/SDL_render.h>

static SDL_Window	*window = nullptr; //Handles game window
static char			*title = (char*) "Imagine Engine Game"; //Handles game window title
static U16			width = 1280; //Handles game window width
static U16			height = 720; //Handles game window height
static S16			x = 500; //Handles game window X position
static S16			y = 200; //Handles game window Y position
static bool			fullscreen = true; //Handles game window fullscreen state
static bool			visible = true; //Handles game window visibility state
static bool			exiting = false; //Handles game window state

S16 Window::create()
{
	if(window != nullptr) return 2;

	window = SDL_CreateWindow(title, x, y, width, height, SDL_WINDOW_OPENGL);

	if(window == nullptr) return 1;

	SDL_GL_CreateContext(window);

	return 0;
}

void Window::firstUpdate()
{
	if(fullscreen) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	if(!visible) SDL_HideWindow(window);
}

void Window::destroy()
{
	if(window == nullptr) return;

	SDL_GL_DeleteContext(SDL_GL_GetCurrentContext());

	SDL_DestroyWindow(window);

	window = nullptr;

	delete window;
}

void Window::update()
{
	if(window == nullptr) return;

	SDL_GL_SwapWindow(window);
}

void Window::shouldExit()
{
	exiting = true;
}

void Window::recreateContext()
{
	if(window == nullptr) return;

	SDL_GL_DeleteContext(SDL_GL_GetCurrentContext());

	SDL_GL_CreateContext(window);
}

void Window::setTitle(char *windowTitle)
{
	title = windowTitle;

	if(window == nullptr) return;

	SDL_SetWindowTitle(window, title);
}

void Window::setWidth(U16 windowWidth)
{
	width = windowWidth;

	if(window == nullptr) return;

	SDL_SetWindowSize(window, width, height);
}

void Window::setHeight(U16 windowHeight)
{
	height = windowHeight;

	if(window == nullptr) return;

	SDL_SetWindowSize(window, width, height);
}

void Window::setPositionX(S16 positionX)
{
	x = positionX;

	if(window == nullptr) return;

	SDL_SetWindowPosition(window, x, y);
}

void Window::setPositionY(S16 positionY)
{
	y = positionY;

	if(window == nullptr) return;

	SDL_SetWindowPosition(window, x, y);
}

void Window::setFullscreen(bool windowFullscreen)
{
	fullscreen = windowFullscreen;

	if(fullscreen) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	else SDL_SetWindowFullscreen(window, 0);
}

void Window::setVisibility(bool windowVisibility)
{
	visible = windowVisibility;

	if(visible) SDL_ShowWindow(window);
	else SDL_HideWindow(window);
}

U16 Window::getWidth()
{
	return width;
}

U16 Window::getHeight()
{
	return height;
}

void Window::cancelExiting()
{
	exiting = false;
}

bool Window::isExiting()
{
	return exiting;
}
