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

#include "face.h"

Face::Face(U64 v1, U64 v2, U64 v3)
{
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;

	this->vt1 = 0.0f;
	this->vt2 = 0.0f;
	this->vt3 = 0.0f;

	this->vn1 = 0.0f;
	this->vn2 = 0.0f;
	this->vn3 = 0.0f;
}

Face::Face(U64 v1, U64 v2, U64 v3, U64 vn1, U64 vn2, U64 vn3)
{
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;

	this->vt1 = 0.0f;
	this->vt2 = 0.0f;
	this->vt3 = 0.0f;

	this->vn1 = vn1;
	this->vn2 = vn2;
	this->vn3 = vn3;
}

Face::Face(U64 v1, U64 v2, U64 v3, U64 vt1, U64 vt2, U64 vt3, U64 vn1, U64 vn2, U64 vn3)
{
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;

	this->vt1 = vt1;
	this->vt2 = vt2;
	this->vt3 = vt3;

	this->vn1 = vn1;
	this->vn2 = vn2;
	this->vn3 = vn3;
}

Face::~Face() {}
