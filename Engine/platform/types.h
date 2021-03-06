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

#ifndef _IE_TYPES_H_
#define _IE_TYPES_H_

typedef signed char				S8;
typedef unsigned char			U8;

typedef signed short			S16;
typedef unsigned short			U16;

typedef signed int				S32;
typedef unsigned int			U32;

#if defined(IMAGINEENGINE_X64)
typedef signed long				S64;
typedef unsigned long			U64;
#else
typedef signed long long		S64;
typedef unsigned long long		U64;
#endif

typedef float					F32;
typedef double					F64;

#endif
