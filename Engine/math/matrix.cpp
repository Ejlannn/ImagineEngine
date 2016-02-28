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

#include "matrix.h"

#include <cmath>

Matrix4::Matrix4()
{
	m00 = 0.0f; m01 = 0.0f; m02 = 0.0f; m03 = 0.0f;
	m10 = 0.0f; m11 = 0.0f; m12 = 0.0f; m13 = 0.0f;
	m20 = 0.0f; m21 = 0.0f; m22 = 0.0f; m23 = 0.0f;
	m30 = 0.0f; m31 = 0.0f; m32 = 0.0f; m33 = 0.0f;
}

Matrix4::Matrix4(F32 m00, F32 m01, F32 m02, F32 m03,
		F32 m10, F32 m11, F32 m12, F32 m13,
		F32 m20, F32 m21, F32 m22, F32 m23,
		F32 m30, F32 m31, F32 m32, F32 m33)
{
	this->m00 = m00; this->m01 = m01; this->m02 = m02; this->m03 = m03;
	this->m10 = m10; this->m11 = m11; this->m12 = m12; this->m13 = m13;
	this->m20 = m20; this->m21 = m21; this->m22 = m22; this->m23 = m23;
	this->m30 = m30; this->m31 = m31; this->m32 = m32; this->m33 = m33;
}

Matrix4::~Matrix4() {}

Matrix4 *Matrix4::clone()
{
	return new Matrix4(m00, m01, m02, m03,
			m10, m11, m12, m13,
			m20, m21, m22, m23,
			m30, m31, m32, m33);
}

void Matrix4::setIdentity()
{
	m00 = 1.0f; m01 = 0.0f; m02 = 0.0f; m03 = 0.0f;
	m10 = 0.0f; m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
	m20 = 0.0f; m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
	m30 = 0.0f; m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
}

void Matrix4::translate(Vector3 *translation)
{
	m30 += m00 * translation->x + m10 * translation->y + m20 * translation->z;
	m31 += m01 * translation->x + m11 * translation->y + m21 * translation->z;
	m32 += m02 * translation->x + m12 * translation->y + m22 * translation->z;
	m33 += m03 * translation->x + m13 * translation->y + m23 * translation->z;
}

void Matrix4::rotate(Vector3 rotation, F32 angle)
{
	F32 c = cosf(angle);
	F32 s = sinf(angle);
	F32 oneminusc = 1.0f - c;
	F32 xy = rotation.x * rotation.y;
	F32 yz = rotation.y * rotation.z;
	F32 xz = rotation.x * rotation.z;
	F32 xs = rotation.x * s;
	F32 ys = rotation.y * s;
	F32 zs = rotation.z * s;

	F32 f00 = rotation.x * rotation.x * oneminusc + c;
	F32 f01 = xy * oneminusc + zs;
	F32 f02 = xz * oneminusc - ys;
	F32 f10 = xy * oneminusc-zs;
	F32 f11 = rotation.y * rotation.y * oneminusc + c;
	F32 f12 = yz*oneminusc+xs;
	F32 f20 = xz*oneminusc+ys;
	F32 f21 = yz*oneminusc-xs;
	F32 f22 = rotation.z * rotation.z * oneminusc + c;

	F32 t00 = m00 * f00 + m10 * f01 + m20 * f02;
	F32 t01 = m01 * f00 + m11 * f01 + m21 * f02;
	F32 t02 = m02 * f00 + m12 * f01 + m22 * f02;
	F32 t03 = m03 * f00 + m13 * f01 + m23 * f02;
	F32 t10 = m00 * f10 + m10 * f11 + m20 * f12;
	F32 t11 = m01 * f10 + m11 * f11 + m21 * f12;
	F32 t12 = m02 * f10 + m12 * f11 + m22 * f12;
	F32 t13 = m03 * f10 + m13 * f11 + m23 * f12;
	m20 = m00 * f20 + m10 * f21 + m20 * f22;
	m21 = m01 * f20 + m11 * f21 + m21 * f22;
	m22 = m02 * f20 + m12 * f21 + m22 * f22;
	m23 = m03 * f20 + m13 * f21 + m23 * f22;
	m00 = t00;
	m01 = t01;
	m02 = t02;
	m03 = t03;
	m10 = t10;
	m11 = t11;
	m12 = t12;
	m13 = t13;
}

void Matrix4::scale(Vector3 *scale)
{
	m00 = m00 * scale->x;
	m01 = m01 * scale->x;
	m02 = m02 * scale->x;
	m03 = m03 * scale->x;
	m10 = m10 * scale->y;
	m11 = m11 * scale->y;
	m12 = m12 * scale->y;
	m13 = m13 * scale->y;
	m20 = m20 * scale->z;
	m21 = m21 * scale->z;
	m22 = m22 * scale->z;
	m23 = m23 * scale->z;
}
