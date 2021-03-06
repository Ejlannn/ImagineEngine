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

#include "game.h"

#include <cstdlib>
#include <SDL2/SDL.h>
#if defined(WIN32) || defined(_WIN64)
#undef main
#endif
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <GL/glew.h>
#include "../../event/event.h"
#include "../../graphics/graphicsDevice.h"
#include "../../graphics/vertexArrayObject.h"

static bool			running = false;
static Scene		*currentScene = nullptr;
static Logger 		*logger = nullptr;
static Game			*currentGame = nullptr;

Game::~Game()
{
	delete logger;
}

S16 Game::initialize()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) return 1;

	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF);

	TTF_Init();

	Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC);

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) return 6;

	logger = new Logger("Imagine Engine");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	GraphicsDevice::preInit();

	if(Window::create() == 1) return 3;

	if(glewInit() != GLEW_OK)
	{
		if(!glewIsSupported("GL_VERSION_3_3")) return 5;
		else return 2;
	}

	Event::init();

	initializeGame();

	GraphicsDevice::init();

	Window::firstUpdate();

	if(currentScene != nullptr) currentScene->initialize();

	return 0; //Returns 0 if everything is OK
}

void Game::update()
{
	Time::start();

	while(running)
	{
		Time::update();
		Event::update();

		currentScene->update();

		GraphicsDevice::render(currentScene);

		if(Window::isExiting() == true) exit();
	}
}

void Game::run()
{
	if(running) return;

	currentGame = this;

	prepareRun();
}

void Game::prepareRun()
{
	S16 result = initialize();

	if(result != 0) Error::throwErrorCode(result);

	running = true;

	update();
}

void Game::exit()
{
	prepareExit();
}

void Game::prepareExit()
{
	if(running) running = false;

	if(currentScene != nullptr) currentScene->destroy();

	if(currentGame != nullptr) currentGame->destroyGame();

	Audio::destroy();

	Event::destroy();

	VertexArrayObject::destroyAll();

	GraphicsDevice::destroy();

	Window::destroy();

	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();

	std::exit(0);
}

bool Game::isRunning()
{
	return running;
}

void Game::setCurrentScene(Scene *scene)
{
	if(running) currentScene->destroy();

	currentScene = scene;

	if(running) currentScene->initialize();
}

Scene *Game::getCurrentScene()
{
	return currentScene;
}

Logger *Game::getLogger()
{
	return logger;
}

void Game::destroyGame() {}
