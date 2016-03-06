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
#include "transformComponent.h"
#include "../../assets/model/modelAsset.h"

class Scene;

class Collision
{
	friend class Scene;

public:
	Entity *getCollider();
	Vector3 getMoveDirection();

private:
	Collision(Entity *entity);

	Entity *collider;
};

class GraphicsDevice;
class BoxColliderComponent;

class MeshColliderComponent : public ComponentBase
{
	friend class Scene;
	friend class GraphicsDevice;
	friend class BoxColliderComponent;

public:
	MeshColliderComponent();

	~MeshColliderComponent();

	bool staticCollider;

private:
	Vector3 *obb[8];

	void createOOB(std::vector<Vector4*> vertices);
	static bool areColliding(Vector3 *obb1[8], Vector3 *obb2[8], ModelAsset *model1, ModelAsset *model2, Matrix4 *transform1, Matrix4 *transform2);
	static bool computeIntervals(F32 vv0, F32 vv1, F32 vv2,
			F32 d0, F32 d1, F32 d2, F32 d0d1, F32 d0d2,
			F32 &a, F32 &b, F32 &c, F32 &x0, F32 &x1);
	static bool coplanar(Vector3 *n, Vector3 *v0, Vector3 *v1, Vector3 *v2,
			Vector3 *u0, Vector3 *u1, Vector3 *u2);
	static bool edgeAgainstTriEdges(Vector3 *v0, Vector3 *v1, Vector3 *u0, Vector3 *u1, Vector3 *u2, S16 i0, S16 i1);
	static bool pointInTri(Vector3 *v0, Vector3 *u0, Vector3 *u1, Vector3 *u2, S16 i0, S16 i1);
	static bool edgeTest(Vector3 *v0, Vector3 *v1, Vector3 *u0, Vector3 *u1, S16 i0, S16 i1);
};

#endif
