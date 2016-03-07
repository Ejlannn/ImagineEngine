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

#ifndef _IE_LOGGER_H_
#define _IE_LOGGER_H_

#include <string>
#include "../platform/types.h"

class Logger
{
public:
	Logger(const std::string &name);
	~Logger();

	void log(const std::string &message);
	void warning(const std::string &message);

	std::string getName() const;

private:
	std::string name;

	void printLog(const std::string &log) const;
	std::string getDateAndTime() const;
};

#endif
