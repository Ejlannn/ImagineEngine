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

#ifndef _IE_FACE_H_
#define _IE_FACE_H_

#include "../platform/types.h"

struct Face
{
	Face(U64 v1, U64 v2, U64 v3);
	Face(U64 v1, U64 v2, U64 v3, U64 vn1, U64 vn2, U64 vn3);
	Face(U64 v1, U64 v2, U64 v3, U64 vt1, U64 vt2, U64 vt3, U64 vn1, U64 vn2, U64 vn3);

	~Face();

	U64 v1, v2, v3;
	U64 vt1, vt2, vt3;
	U64 vn1, vn2, vn3;
};

#endif
