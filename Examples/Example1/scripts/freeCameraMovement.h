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

#ifndef _IE_FREE_CAMERA_MOVEMENT_H_
#define _IE_FREE_CAMERA_MOVEMENT_H_

#include "../../../Engine/engine/script.h"

class FreeCameraMovement : public Script
{
public:
	virtual void onInit();
	virtual void onUpdate();
	virtual void onDestroy();

	FilePath *shotSound;
	FilePath *font1;
};

#endif
