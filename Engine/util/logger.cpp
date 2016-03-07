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

#include "logger.h"

#include <iostream>
#include <ctime>

Logger::Logger(const std::string &name)
{
	this->name = name;
}

Logger::~Logger() {}

void Logger::log(const std::string &message)
{
	printLog(getDateAndTime() + " [" + name + "] " + message);
}

void Logger::warning(const std::string &message)
{
	printLog(getDateAndTime() + " [" + name + "]" + " [Warning] " + message);
}

void Logger::printLog(const std::string &log) const
{
	std::cout << log.c_str() << std::endl;
}

std::string Logger::getName() const
{
	return name.c_str();
}

std::string Logger::getDateAndTime() const
{
	time_t timeNow = time(0);
	struct tm tStruct;
	char buffer[80];
	tStruct = *std::localtime(&timeNow);

	strftime(buffer, sizeof(buffer), "[%Y-%m-%d %X]", &tStruct);

	return buffer;
}
