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

#include "color.h"

/******************************
 * Color3
 *****************************/
Color3::Color3()
{
	r = 0.0f;
	g = 0.0f;
	b = 0.0f;
}


Color3::Color3(F32 value)
{
	r = value;
	g = value;
	b = value;
}

Color3::Color3(F32 r, F32 g, F32 b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

Color3::~Color3()
{
	delete &r;
	delete &g;
	delete &b;
}

Color3 *Color3::clone()
{
	return new Color3(r, g, b);
}

/******************************
 * Color4
 *****************************/
Color4::Color4()
{
	r = 0.0f;
	g = 0.0f;
	b = 0.0f;
	a = 0.0f;
}

Color4::Color4(F32 value)
{
	r = value;
	g = value;
	b = value;
	a = value;
}

Color4::Color4(Color3 *color3, F32 a)
{
	r = color3->r;
	g = color3->g;
	b = color3->b;
	this->a = a;
}

Color4::Color4(F32 r, F32 g, F32 b, F32 a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color4::~Color4()
{
	delete &r;
	delete &g;
	delete &b;
	delete &a;
}

Color4 *Color4::clone()
{
	return new Color4(r, g, b, a);
}
