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

#ifndef _IE_CONSOLE_H_
#define _IE_CONSOLE_H_

#include "commandExecutor.h"
#include "../../math/math.h"
#include "../../input/keyboardInput.h"

class CommandExecutor;
class GraphicsDevice;
class Event;

class Console
{
	friend class GraphicsDevice;
	friend class Event;

public:
	static void registerCommandExecutor(CommandExecutor *commandExecutor);
	static void sendMessage(std::string message);

	static bool isVisible();

private:
	static std::vector<std::string> getLines();
	static std::string getCurrentLine();
	static void setVisibility(bool vis);
	static void switchVis();
	static void onConsoleKeyDown(KeyboardKey key, bool big);
	static void destroy();
};

#endif
