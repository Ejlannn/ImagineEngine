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

#ifndef _IE_SCRIPT_H_
#define _IE_SCRIPT_H_

#include "game/game.h"

class ScriptComponent;
class Event;
class Scene;

class Script
{
	friend class ScriptComponent;
	friend class Event;
	friend class Scene;

public:
	virtual ~Script();

private:
	Entity *entity;

protected:
	Entity *getEntity();

	virtual void onInit();
	virtual void onUpdate();
	virtual void onDestroy();
	virtual void onKeyboardKeyDown(KeyboardKey key);
	virtual void onMouseButtonDown(MouseButton button);
	virtual void onCollision(Collision collision);
};

#endif
