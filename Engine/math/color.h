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

#ifndef _IE_COLOR_H_
#define _IE_COLOR_H_

#include "../platform/types.h"

/******************************
 * Color3
 *****************************/
struct Color3
{
	Color3();
	Color3(F32 value);
	Color3(F32 r, F32 g, F32 b);

	~Color3();

	F32 r;
	F32 g;
	F32 b;

	Color3 *clone();

	static Color3 getFromHEX(U32 hexColor);
	void setFromHEX(U32 hexColor);
};

/******************************
 * Color4
 *****************************/
struct Color4
{
	Color4();
	Color4(F32 value);
	Color4(Color3 *color3, F32 a);
	Color4(F32 r, F32 g, F32 b, F32 a);

	~Color4();

	F32 r;
	F32 g;
	F32 b;
	F32 a;

	Color4 *clone();
};

#endif
