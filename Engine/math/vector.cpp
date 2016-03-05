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

#include "vector.h"

#include <algorithm>
#include <cmath>
#include "matrix.h"

/******************************
 * Vector2
 *****************************/
Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2::Vector2(F32 value)
{
	x = value;
	y = value;
}

Vector2::Vector2(F32 x, F32 y)
{
	this->x = x;
	this->y = y;
}

Vector2::~Vector2() {}

Vector2 *Vector2::clone()
{
	return new Vector2(x, y);
}

/******************************
 * Vector3
 *****************************/
Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector3::Vector3(F32 value)
{
	x = value;
	y = value;
	z = value;
}

Vector3::Vector3(Vector2 *vector2, F32 z)
{
	x = vector2->x;
	y = vector2->y;
	this->z = z;
}

Vector3::Vector3(F32 x, F32 y, F32 z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::~Vector3() {}

Vector3 *Vector3::clone()
{
	return new Vector3(x, y, z);
}

bool Vector3::isNormalized()
{
	return abs((x * x) + (y * y) + (z * z) - 1.0f) < F32(1e-6f);
}

void Vector3::normalize()
{
	F32 length = this->length();

	if (length > F32(1e-6f))
	{
		F32 inv = 1.0f / length;

		x *= inv;
		y *= inv;
		z *= inv;
	}
}

F32 Vector3::length(Vector3 *value)
{
	return length(Vector3(value->x, value->y, value->z));
}

F32 Vector3::length(Vector3 value)
{
	return sqrtf((value.x * value.x) + (value.y * value.y) + (value.z * value.z));
}

F32 Vector3::length()
{
	return length(this);
}

F32 Vector3::lengthSquared(Vector3 *value)
{
	return lengthSquared(Vector3(value->x, value->y, value->z));
}

F32 Vector3::lengthSquared(Vector3 value)
{
	return (value.x * value.x) + (value.y * value.x) + (value.z * value.z);
}

F32 Vector3::lengthSquared()
{
	return lengthSquared(this);
}

F32 Vector3::distance(Vector3 *value1, Vector3 *value2)
{
	return distance(Vector3(value1->x, value1->y, value1->z), Vector3(value2->x, value2->y, value2->z));
}

F32 Vector3::distance(Vector3 value1, Vector3 value2)
{
	F32 tempX = value1.x - value2.x;
	F32 tempY = value1.y - value2.y;
	F32 tempZ = value1.z - value2.z;

	return sqrtf((tempX * tempX) + (tempY * tempY) + (tempZ * tempZ));
}

F32 Vector3::distance(Vector3 *value1, Vector3 value2)
{
	return distance(Vector3(value1->x, value1->y, value1->z), value2);
}

F32 Vector3::distance(Vector3 value1, Vector3 *value2)
{
	return distance(value1, Vector3(value2->x, value2->y, value2->z));
}

F32 Vector3::distance(Vector3 *value)
{
	return distance(this, value);
}

F32 Vector3::distance(Vector3 value)
{
	return distance(this, value);
}

Vector3 *Vector3::add(Vector3 *value1, Vector3 *value2)
{
	return new Vector3(value1->x + value2->x, value1->y + value2->y, value1->z + value2->z);
}

Vector3 *Vector3::subtract(Vector3 *value1, Vector3 *value2)
{
	return new Vector3(value1->x - value2->x, value1->y - value2->y, value1->z - value2->z);
}

F32 Vector3::dot(Vector3 *value1, Vector3 *value2)
{
	return (value1->x * value2->x) + (value1->y * value2->y) + (value1->z * value2->z);
}

Vector3 *Vector3::cross(Vector3 *value1, Vector3 *value2)
{
	return new Vector3((value1->y * value2->z) - (value1->z * value2->y),
			(value1->z * value2->x) - (value1->x * value2->z),
			(value1->x * value2->y) - (value1->y * value2->x));
}

/******************************
 * Vector4
 *****************************/
Vector4::Vector4()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

Vector4::Vector4(F32 value)
{
	x = value;
	y = value;
	z = value;
	w = value;
}

Vector4::Vector4(Vector2 *vector2, F32 z, F32 w)
{
	x = vector2->x;
	y = vector2->y;
	this->z = z;
	this->w = w;
}

Vector4::Vector4(Vector3 *vector3, F32 w)
{
	x = vector3->x;
	y = vector3->y;
	z = vector3->z;
	this->w = w;
}

Vector4::Vector4(F32 x, F32 y, F32 z, F32 w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4::~Vector4() {}


Vector4 *Vector4::clone()
{
	return new Vector4(x, y, z, w);
}

F32 Vector4::distance(Vector4 *value1, Vector4 *value2)
{
	F32 tempX = value1->x - value2->x;
	F32 tempY = value1->y - value2->y;
	F32 tempZ = value1->z - value2->z;
	F32 tempW = value1->w - value2->w;

	return sqrtf((tempX * tempX) + (tempY * tempY) + (tempZ * tempZ) + (tempW * tempW));
}

Vector4 *Vector4::transform(Vector4 *vector4, Matrix4 *matrix)
{
	Vector4 *result = new Vector4((vector4->x * matrix->m00) + (vector4->y * matrix->m10) + (vector4->z * matrix->m20) + (vector4->w * matrix->m30),
			(vector4->x * matrix->m01) + (vector4->y * matrix->m11) + (vector4->z * matrix->m21) + (vector4->w * matrix->m31),
			(vector4->x * matrix->m02) + (vector4->y * matrix->m12) + (vector4->z * matrix->m22) + (vector4->w * matrix->m32),
			(vector4->x * matrix->m03) + (vector4->y * matrix->m13) + (vector4->z * matrix->m23) + (vector4->w * matrix->m33));

	return result;
}

void Vector4::transform(Matrix4 *matrix)
{
	Vector4 *result = transform(this, matrix);

	x = result->x;
	y = result->y;
	z = result->z;
	w = result->w;

	delete result;
}
