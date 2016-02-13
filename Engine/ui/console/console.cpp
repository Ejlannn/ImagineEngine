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

#include "console.h"

std::vector<CommandExecutor*>	commandExecutors;
std::vector<std::string>		lines;
static bool 					shown = false;
std::string						tempCurrentLine = "";
std::vector<std::string>		currentLineBuf;

void Console::registerCommandExecutor(CommandExecutor *commandExecutor)
{
	for(U16 i = 0; i < commandExecutors.size(); i++)
	{
		if(commandExecutors.at(i) == commandExecutor) return;
	}

	commandExecutors.push_back(commandExecutor);
}

void Console::sendMessage(std::string message)
{
	lines.push_back(message);
}

bool Console::isVisible()
{
	return shown;
}

std::vector<std::string> Console::getLines()
{
	return lines;
}

std::string Console::getCurrentLine()
{
	std::string currentLine = "";

	if(currentLineBuf.size() > 0)
	{
		for(U16 i = 0; i < currentLineBuf.size(); i++)
		{
			currentLine += currentLineBuf.at(i);
			currentLine += " ";
		}
	}

	currentLine += tempCurrentLine;

	return currentLine;
}

void Console::setVisibility(bool vis)
{
	shown = vis;
}

void Console::switchVis()
{
	if(shown) shown = false;
	else shown = true;
}

void Console::onConsoleKeyDown(KeyboardKey key, bool big)
{
	switch(key)
	{
	case KeyboardKey::KEY_RETURN:
		if(tempCurrentLine.size() == 0 && currentLineBuf.size() == 0) return;
		if(currentLineBuf.size() > 0)
		{
			std::string cmd;
			std::string args[currentLineBuf.size()];

			for(U16 j = 0; j < currentLineBuf.size(); j++)
			{
				if(j == 0) cmd = currentLineBuf.at(j);
				else
				{
					args[j] = currentLineBuf.at(j);
				}
			}

			for(U16 i = 0; i < commandExecutors.size(); i++)
			{
				commandExecutors.at(i)->onCommand(cmd, args);
			}
		}
		else
		{
			for(U16 i = 0; i < commandExecutors.size(); i++)
			{
				std::string args[0];
				commandExecutors.at(i)->onCommand(tempCurrentLine, args);
			}
		}
		tempCurrentLine = "";
		currentLineBuf.clear();
		break;
	case KeyboardKey::KEY_BACKSPACE:
		if(tempCurrentLine.size() > 0) tempCurrentLine = tempCurrentLine.substr(0, tempCurrentLine.size() - 1);
		else
		{
			if(currentLineBuf.size() > 0)
			{
				tempCurrentLine = currentLineBuf.at(currentLineBuf.size() - 1);
				currentLineBuf.erase(currentLineBuf.end() - 1);
			}
			else return;
		}
		break;
	case KeyboardKey::KEY_SPACE:
		currentLineBuf.push_back(tempCurrentLine);
		tempCurrentLine = "";
		break;
	default:
		switch(key)
		{
		case KeyboardKey::KEY_1:
			tempCurrentLine += "1";
			break;
		case KeyboardKey::KEY_2:
			tempCurrentLine += "2";
			break;
		case KeyboardKey::KEY_3:
			tempCurrentLine += "3";
			break;
		case KeyboardKey::KEY_4:
			tempCurrentLine += "4";
			break;
		case KeyboardKey::KEY_5:
			tempCurrentLine += "5";
			break;
		case KeyboardKey::KEY_6:
			tempCurrentLine += "6";
			break;
		case KeyboardKey::KEY_7:
			tempCurrentLine += "7";
			break;
		case KeyboardKey::KEY_8:
			tempCurrentLine += "8";
			break;
		case KeyboardKey::KEY_9:
			tempCurrentLine += "9";
			break;
		case KeyboardKey::KEY_0:
			tempCurrentLine += "0";
			break;
		case KeyboardKey::KEY_MINUS:
			if(big) tempCurrentLine += "_";
			else tempCurrentLine += "-";
			break;
		case KeyboardKey::KEY_EQUALS:
			if(big) tempCurrentLine += "+";
			else tempCurrentLine += "=";
			break;
		case KeyboardKey::KEY_Q:
			if(big) tempCurrentLine += "Q";
			else tempCurrentLine += "q";
			break;
		case KeyboardKey::KEY_W:
			if(big) tempCurrentLine += "W";
			else tempCurrentLine += "w";
			break;
		case KeyboardKey::KEY_E:
			if(big) tempCurrentLine += "E";
			else tempCurrentLine += "e";
			break;
		case KeyboardKey::KEY_R:
			if(big) tempCurrentLine += "R";
			else tempCurrentLine += "r";
			break;
		case KeyboardKey::KEY_T:
			if(big) tempCurrentLine += "T";
			else tempCurrentLine += "t";
			break;
		case KeyboardKey::KEY_Y:
			if(big) tempCurrentLine += "Y";
			else tempCurrentLine += "y";
			break;
		case KeyboardKey::KEY_U:
			if(big) tempCurrentLine += "U";
			else tempCurrentLine += "u";
			break;
		case KeyboardKey::KEY_I:
			if(big) tempCurrentLine += "I";
			else tempCurrentLine += "i";
			break;
		case KeyboardKey::KEY_O:
			if(big) tempCurrentLine += "O";
			else tempCurrentLine += "o";
			break;
		case KeyboardKey::KEY_P:
			if(big) tempCurrentLine += "P";
			else tempCurrentLine += "p";
			break;
		case KeyboardKey::KEY_A:
			if(big) tempCurrentLine += "A";
			else tempCurrentLine += "a";
			break;
		case KeyboardKey::KEY_S:
			if(big) tempCurrentLine += "S";
			else tempCurrentLine += "s";
			break;
		case KeyboardKey::KEY_D:
			if(big) tempCurrentLine += "D";
			else tempCurrentLine += "d";
			break;
		case KeyboardKey::KEY_F:
			if(big) tempCurrentLine += "F";
			else tempCurrentLine += "f";
			break;
		case KeyboardKey::KEY_G:
			if(big) tempCurrentLine += "G";
			else tempCurrentLine += "g";
			break;
		case KeyboardKey::KEY_H:
			if(big) tempCurrentLine += "H";
			else tempCurrentLine += "h";
			break;
		case KeyboardKey::KEY_J:
			if(big) tempCurrentLine += "J";
			else tempCurrentLine += "j";
			break;
		case KeyboardKey::KEY_K:
			if(big) tempCurrentLine += "K";
			else tempCurrentLine += "k";
			break;
		case KeyboardKey::KEY_L:
			if(big) tempCurrentLine += "L";
			else tempCurrentLine += "l";
			break;
		case KeyboardKey::KEY_Z:
			if(big) tempCurrentLine += "Z";
			else tempCurrentLine += "z";
			break;
		case KeyboardKey::KEY_X:
			if(big) tempCurrentLine += "X";
			else tempCurrentLine += "x";
			break;
		case KeyboardKey::KEY_C:
			if(big) tempCurrentLine += "C";
			else tempCurrentLine += "c";
			break;
		case KeyboardKey::KEY_V:
			if(big) tempCurrentLine += "V";
			else tempCurrentLine += "v";
			break;
		case KeyboardKey::KEY_B:
			if(big) tempCurrentLine += "B";
			else tempCurrentLine += "b";
			break;
		case KeyboardKey::KEY_N:
			if(big) tempCurrentLine += "N";
			else tempCurrentLine += "n";
			break;
		case KeyboardKey::KEY_M:
			if(big) tempCurrentLine += "M";
			else tempCurrentLine += "m";
			break;
		}
	}
}
