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

#ifndef _IE_VECTOR_H_
#define _IE_VECTOR_H_

#include "../platform/types.h"

class Matrix4;

/******************************
 * Vector2
 *****************************/
struct Vector2
{
	Vector2();
	Vector2(F32 value);
	Vector2(F32 x, F32 y);

	~Vector2();

	F32 x;
	F32 y;

	Vector2 *clone();
};

/******************************
 * Vector3
 *****************************/
struct Vector3
{
	Vector3();
	Vector3(F32 value);
	Vector3(Vector2 *vector2, F32 z);
	Vector3(F32 x, F32 y, F32 z);

	~Vector3();

	F32 x;
	F32 y;
	F32 z;

	Vector3 *clone();

	bool isNormalized();

	void normalize();

	static F32 length(Vector3 *value);
	static F32 length(Vector3 value);
	F32 length();

	static F32 lengthSquared(Vector3 *value);
	static F32 lengthSquared(Vector3 value);
	F32 lengthSquared();

	static F32 distance(Vector3 *value1, Vector3 *value2);
	static F32 distance(Vector3 value1, Vector3 value2);
	static F32 distance(Vector3 *value1, Vector3 value2);
	static F32 distance(Vector3 value1, Vector3 *value2);
	F32 distance(Vector3 *value);
	F32 distance(Vector3 value);

	static Vector3 *add(Vector3 *value1, Vector3 *value2);

	static Vector3 *subtract(Vector3 *value1, Vector3 *value2);

	static F32 dot(Vector3 *value1, Vector3 *value2);

	static Vector3 *cross(Vector3 *value1, Vector3 *value2);
};

/******************************
 * Vector4
 *****************************/
struct Vector4
{
	Vector4();
	Vector4(F32 value);
	Vector4(Vector2 *vector2, F32 z, F32 w);
	Vector4(Vector3 *vector3, F32 w);
	Vector4(F32 x, F32 y, F32 z, F32 w);

	~Vector4();

	F32 x;
	F32 y;
	F32 z;
	F32 w;

	Vector4 *clone();

	static F32 distance(Vector4 *value1, Vector4 *value2);

	void transform(Matrix4 *matrix);
	static Vector4 *transform(Vector4 *vector4, Matrix4 *matrix);
};

#endif
