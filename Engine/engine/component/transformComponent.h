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

#ifndef _IE_TRANSFORM_COMPONENT_H_
#define _IE_TRANSFORM_COMPONENT_H_

#include "componentBase.h"

class GraphicsDevice;

class TransformComponent : public ComponentBase
{
	friend class GraphicsDevice;

public:
	TransformComponent();
	TransformComponent(Vector3 *position);
	TransformComponent(Vector3 *position, Vector3 *rotation, Vector3 *scale);

	~TransformComponent();

	Vector3 *position;
	Vector3 *rotation;
	Vector3 *scale;

private:
	static Matrix4 *createTransformationMatrix(TransformComponent *component);
	static Matrix4 *createTransformationMatrix(Vector3 *translation, Vector3 *rotation, Vector3 *scale);
};

#endif
