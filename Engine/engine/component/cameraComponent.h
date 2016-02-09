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

#ifndef _IE_CAMERA_COMPONENT_H_
#define _IE_CAMERA_COMPONENT_H_

#include "componentBase.h"

class GraphicsDevice;

class CameraComponent : public ComponentBase
{
	friend class GraphicsDevice;

public:
	CameraComponent();

	~CameraComponent();

	F32 nearPlane;
	F32 farPlane;
	F32 fov;

	F32 yaw;
	F32 pitch;

private:
	static Matrix4 *createProjectionMatrix(CameraComponent *camera);
	static Matrix4 *create2DOrthoProjectionMatrix();
	static Matrix4 *createViewMatrix(CameraComponent *camera);
};

#endif
