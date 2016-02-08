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

#ifndef _IE_LIGHT_H_
#define _IE_LIGHT_H_

#include <string>
#include "../math/math.h"

class Entity;
class LightProcessor;
class Scene;

class Light
{
	friend class LightProcessor;
	friend class Scene;

public:
	Color3 *color;
	F32 intensity;

	~Light();

protected:
	Light(std::string type);

private:
	std::string type;
	Entity *entity;
};

#endif
