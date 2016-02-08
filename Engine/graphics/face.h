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

class Face
{
public:
	Face(S32 v1, S32 v2, S32 v3);
	Face(S32 v1, S32 v2, S32 v3, S32 vn);
	Face(S32 v1, S32 v2, S32 v3, S32 vt1, S32 vt2, S32 vt3);
	Face(S32 v1, S32 v2, S32 v3, S32 vt1, S32 vt2, S32 vt3, S32 vn);


	S32 v1, v2, v3;
	S32 vt1, vt2, vt3;
	S32 vn;
};

#endif
