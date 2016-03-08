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

#include "mathUtil.h"

F32 MathUtil::degToRad(F32 deg)
{
	return deg * (PI / 180.0f);
}

F32 MathUtil::radToDeg(F32 rad)
{
	return rad * (180.0f / PI);
}

F32 MathUtil::clamp(F32 value, F32 min, F32 max)
{
	F32 valueToReturn = value;

	if(valueToReturn < min) valueToReturn = min;
	else if(valueToReturn > max) valueToReturn = max;

	return valueToReturn;
}

void MathUtil::clamp(F32 &value, F32 min, F32 max)
{
	if(value < min) value = min;
	else if(value > max) value = max;
}

F32 MathUtil::min(F32 value, F32 min)
{
	F32 valueToReturn = value;

	if(valueToReturn < min) valueToReturn = min;

	return valueToReturn;
}

void MathUtil::min(F32 &value, F32 min)
{
	if(value < min) value = min;
}

F32 MathUtil::max(F32 value, F32 max)
{
	F32 valueToReturn = value;

	if(valueToReturn > max) valueToReturn = max;

	return valueToReturn;
}

void MathUtil::max(F32 &value, F32 max)
{
	if(value > max) value = max;
}
