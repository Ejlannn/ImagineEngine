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

#ifndef _IE_MATRIX_H_
#define _IE_MATRIX_H_

#include "vector.h"
#include "../platform/types.h"

struct Matrix4
{
	Matrix4();
	Matrix4(F32 m00, F32 m01, F32 m02, F32 m03,
			F32 m10, F32 m11, F32 m12, F32 m13,
			F32 m20, F32 m21, F32 m22, F32 m23,
			F32 m30, F32 m31, F32 m32, F32 m33);

	F32 m00, m01, m02, m03;
	F32 m10, m11, m12, m13;
	F32 m20, m21, m22, m23;
	F32 m30, m31, m32, m33;

	~Matrix4();

	Matrix4 *clone();

	void setIdentity();

	void translate(Vector3 *translation);
	void rotate(Vector3 *rotation, F32 angle);
	void scale(Vector3 *scale);
};

#endif
