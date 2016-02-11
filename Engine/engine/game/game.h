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

#ifndef _IE_GAME_H_
#define _IE_GAME_H_

#if defined(_WIN32) || defined(_WIN64) || defined(__APPLE__) || defined (__linux__)

#include "../scene.h"
#include "../light/light.h"
#include "../../assets/assets.h"
#include "../../audio/audio.h"
#include "../../error/error.h"
#include "../../input/input.h"
#include "../../platform/types.h"
#include "../../time/time.h"
#include "../../ui/ui.h"
#include "../../window/window.h"

class Game
{
public:
	virtual ~Game();

	void run();
	static void exit();

	static bool isRunning();

	static void setCurrentScene(Scene *scene);

	static Scene *getCurrentScene();

private:
	S16 initialize();
	void prepareRun();
	static void prepareExit();
	void update();

protected:
	virtual void initializeGame() = 0;
};

#endif
#endif
