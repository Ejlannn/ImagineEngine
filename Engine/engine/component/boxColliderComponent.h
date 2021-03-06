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

#ifndef _IE_BOX_COLLIDER_COMPONENT_H_
#define _IE_BOX_COLLIDER_COMPONENT_H_

#include "componentBase.h"
#include "meshColliderComponent.h"
#include "../../assets/model/modelAsset.h"

class Scene;

class BoxColliderComponent : public ComponentBase
{
	friend class Scene;
	friend class MeshColliderComponent;

public:
	BoxColliderComponent();
	BoxColliderComponent(F32 size);
	BoxColliderComponent(F32 width, F32 height, F32 depth);

	~BoxColliderComponent();

	F32 width;
	F32 height;
	F32 depth;
	bool staticCollider;

private:
	Vector3 *obb[8];
	ModelAsset *modelAsset;
	BoxCollisionFace face;

	void create(Vector3 *position);
};

#endif
