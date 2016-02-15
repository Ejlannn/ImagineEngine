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

#ifndef _IE_MESH_COLLIDER_COMPONENT_H_
#define _IE_MESH_COLLIDER_COMPONENT_H_

#include "componentBase.h"
#include "../../assets/model/modelAsset.h"

class Scene;

class Collision
{
	friend class Scene;
public:
	Entity *getCollider();

private:
	Collision(Entity *entity)
	{
		collider = entity;
	}

	Entity *collider;
};

class GraphicsDevice;

/*
 * IMPORTANT: MeshColliderComponent is incomplete, it detects collisions only for 2 Oriented Bounding Boxes (Not detailed collision for mesh yet)
 */
class MeshColliderComponent : public ComponentBase
{
	friend class Scene;
	friend class GraphicsDevice;

public:
	MeshColliderComponent();

	~MeshColliderComponent();

	bool staticCollider;

private:
	Vector3 *obb[8];

	void createOOB(std::vector<Vector4*> vertices);
	static bool areColliding(Vector3 *obb1[8], Vector3 *obb2[8], std::vector<Vector4*> vertices1, std::vector<Vector4*> vertices2);
};

#endif
