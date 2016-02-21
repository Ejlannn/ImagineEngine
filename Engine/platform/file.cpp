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

#include "file.h"

#include <fstream>
#include <SDL2/SDL_filesystem.h>
#include "../error/error.h"

FilePath::FilePath(const std::string &path)
{
	if(!exist(path.c_str()))
	{
		char *line1 = (char*) "File not found:\n";

		std::string msgTemp;
		msgTemp += line1;
		msgTemp += path;

		char *message = &msgTemp[0u];

		Error::throwError(message);
	}
	else this->path = path;
}

FilePath::~FilePath() {}

FilePath *FilePath::getFileFromGamePath(const std::string &file)
{
	char *exePath = FilePath::getGamePath();

	std::string fullPath;

	fullPath += exePath;
	fullPath += file;

	return new FilePath(fullPath.c_str());
}

bool FilePath::exist(const std::string &path)
{
	std::ifstream file(path.c_str());

	return file;
}

std::string FilePath::getPath() const
{
	return path.c_str();
}

char *FilePath::getGamePath()
{
	return SDL_GetBasePath();
}
