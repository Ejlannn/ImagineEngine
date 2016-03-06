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

#include "meshColliderComponent.h"

#include <algorithm>
#include <cfloat>
#include <cmath>

Collision::Collision(Entity *entity)
{
	collider = entity;
}

MeshColliderComponent::MeshColliderComponent() : ComponentBase("MeshColliderComponent")
{
	staticCollider = true;

	for(U16 i = 0; i < 8; i++) obb[i] = nullptr;
}

MeshColliderComponent::~MeshColliderComponent() {}

void MeshColliderComponent::createOOB(std::vector<Vector4*> vertices)
{
	for(U16 i = 0; i < 8; i++) if(obb[i] != nullptr) delete obb[i];

	F32 minX;
	F32 minY;
	F32 minZ;
	F32 maxX;
	F32 maxY;
	F32 maxZ;

	for(U32 i = 0; i < vertices.size(); i++)
	{
		if(i == 0)
		{
			minX = vertices.at(i)->x;
			minY = vertices.at(i)->y;
			minZ = vertices.at(i)->z;
			maxX = vertices.at(i)->x;
			maxY = vertices.at(i)->y;
			maxZ = vertices.at(i)->z;

			continue;
		}

		Vector3 *currentVertex = new Vector3(vertices.at(i)->x, vertices.at(i)->y, vertices.at(i)->z);

		if(currentVertex->x < minX) minX = currentVertex->x;
		else if(currentVertex->x > maxX) maxX = currentVertex->x;
		else if(currentVertex->y < minY) minY = currentVertex->y;
		else if(currentVertex->y > maxY) maxY = currentVertex->y;
		else if(currentVertex->z < minZ) minZ = currentVertex->z;
		else if(currentVertex->z > maxZ) maxZ = currentVertex->z;

		delete currentVertex;
	}

	obb[0] = new Vector3(minX, maxY, maxZ);
	obb[1] = new Vector3(maxX, maxY, maxZ);
	obb[2] = new Vector3(minX, maxY, minZ);
	obb[3] = new Vector3(maxX, maxY, minZ);
	obb[4] = new Vector3(minX, minY, maxZ);
	obb[5] = new Vector3(maxX, minY, maxZ);
	obb[6] = new Vector3(minX, minY, minZ);
	obb[7] = new Vector3(maxX, minY, minZ);
}

bool MeshColliderComponent::areColliding(Vector3 *obb1[8], Vector3 *obb2[8], ModelAsset *model1, ModelAsset *model2, Matrix4 *transform1, Matrix4 *transform2)
{
	bool obbResult = false;

	for(U16 i = 0; i < 8; i++)
	{
		Vector3 *currentOBBVertex = obb1[i];

		Vector3 *min = obb2[6];
		Vector3 *max = obb2[1];

		if((currentOBBVertex->x >= min->x && currentOBBVertex->x <= max->x) && (currentOBBVertex->y >= min->y && currentOBBVertex->y <= max->y) && (currentOBBVertex->z >= min->z && currentOBBVertex->z <= max->z))
		{
			obbResult = true;

			break;
		}

		delete currentOBBVertex;
		delete min;
		delete max;
	}

	if(obbResult == false) return false;
	//else return true;

	std::vector<Vector3*> vertices1;
	std::vector<Vector3*> vertices2;

	for(U64 i = 0; i < model1->faces.size(); i++)
	{
		Vector4 *vertex1 = new Vector4(model1->vertices.at(model1->faces.at(i)->v1 - 1), 0.0f);
		Vector4 *vertex2 = new Vector4(model1->vertices.at(model1->faces.at(i)->v2 - 1), 0.0f);
		Vector4 *vertex3 = new Vector4(model1->vertices.at(model1->faces.at(i)->v3 - 1), 0.0f);

		vertex1->transform(transform1);
		vertex2->transform(transform1);
		vertex3->transform(transform1);

		vertices1.push_back(new Vector3(vertex1->x, vertex1->y, vertex1->z));
		vertices1.push_back(new Vector3(vertex2->x, vertex2->y, vertex2->z));
		vertices1.push_back(new Vector3(vertex3->x, vertex3->y, vertex3->z));

		delete vertex1;
		delete vertex2;
		delete vertex3;
	}

	for(U64 i = 0; i < model2->faces.size(); i++)
	{
		Vector4 *vertex1 = new Vector4(model2->vertices.at(model2->faces.at(i)->v1 - 1), 0.0f);
		Vector4 *vertex2 = new Vector4(model2->vertices.at(model2->faces.at(i)->v2 - 1), 0.0f);
		Vector4 *vertex3 = new Vector4(model2->vertices.at(model2->faces.at(i)->v3 - 1), 0.0f);

		vertex1->transform(transform2);
		vertex2->transform(transform2);
		vertex3->transform(transform2);

		vertices2.push_back(new Vector3(vertex1->x, vertex1->y, vertex1->z));
		vertices2.push_back(new Vector3(vertex2->x, vertex2->y, vertex2->z));
		vertices2.push_back(new Vector3(vertex3->x, vertex3->y, vertex3->z));

		delete vertex1;
		delete vertex2;
		delete vertex3;
	}

	for(U64 i = 0; i < vertices1.size() / 3; i++)
	{
		for(U64 j = 0; j < vertices2.size() / 3; j++)
		{
			Vector3 *vertex1_1 = vertices1.at(i * 3);
			Vector3 *vertex1_2 = vertices1.at(i * 3 + 1);
			Vector3 *vertex1_3 = vertices1.at(i * 3 + 2);

			Vector3 *vertex2_1 = vertices2.at(j * 3);
			Vector3 *vertex2_2 = vertices2.at(j * 3 + 1);
			Vector3 *vertex2_3 = vertices2.at(j * 3 + 2);

			Vector3 *e1 = Vector3::subtract(vertex1_2, vertex1_1);
			Vector3 *e2 = Vector3::subtract(vertex1_3, vertex1_1);

			Vector3 *n1 = Vector3::cross(e1, e2);

			F32 d1 = -Vector3::dot(n1, vertex1_1);

			F32 du0 = Vector3::dot(n1, vertex2_1) + d1;
			F32 du1 = Vector3::dot(n1, vertex2_2) + d1;
			F32 du2 = Vector3::dot(n1, vertex2_3) + d1;

			if(abs(du0) < F32(FLT_EPSILON)) du0 = 0.0f;
			if(abs(du1) < F32(FLT_EPSILON)) du1 = 0.0f;
			if(abs(du2) < F32(FLT_EPSILON)) du2 = 0.0f;

			F32 du0du1 = du0 * du1;
			F32 du0du2 = du0 * du2;

			if(du0du1 > 0.0f && du0du2 > 0.0f)
			{
				delete e1;
				delete e2;
				delete n1;

				continue;
			}

			delete e1;
			delete e2;

			e1 = Vector3::subtract(vertex2_2, vertex2_1);
			e2 = Vector3::subtract(vertex2_3, vertex2_1);

			Vector3 *n2 = Vector3::cross(e1, e2);

			F32 d2 = -Vector3::dot(n2, vertex2_1);

			F32 dv0 = Vector3::dot(n2, vertex1_1) + d2;
			F32 dv1 = Vector3::dot(n2, vertex1_2) + d2;
			F32 dv2 = Vector3::dot(n2, vertex1_3) + d2;

			if(abs(dv0) < F32(FLT_EPSILON)) dv0 = 0.0f;
			if(abs(dv1) < F32(FLT_EPSILON)) dv1 = 0.0f;
			if(abs(dv2) < F32(FLT_EPSILON)) dv2 = 0.0f;

			F32 dv0dv1 = dv0 * dv1;
			F32 dv0dv2 = dv0 * dv2;

			if(dv0dv1 > 0.0f && dv0dv2 > 0.0f)
			{
				delete e1;
				delete e2;
				delete n1;
				delete n2;

				continue;
			}

			Vector3 *dd = Vector3::cross(n1, n2);

			F32 max = (F32) abs(dd->x);

			S16 index = 0;

			F32 bb = (F32) abs(dd->y);

			F32 cc = (F32) abs(dd->z);

			if(bb > max)
			{
				max = bb;
				index = 1;
			}

			if(cc > max)
			{
				max = cc;
				index = 2;
			}

			F32 vp0;

			if(index == 0) vp0 = vertex1_1->x;
			else if(index == 1) vp0 = vertex1_1->y;
			else if(index == 2) vp0 = vertex1_1->z;

			F32 vp1;

			if(index == 0) vp1 = vertex1_2->x;
			else if(index == 1) vp1 = vertex1_2->y;
			else if(index == 2) vp1 = vertex1_2->z;

			F32 vp2;

			if(index == 0) vp2 = vertex1_3->x;
			else if(index == 1) vp2 = vertex1_3->y;
			else if(index == 2) vp2 = vertex1_3->z;

			F32 up0;

			if(index == 0) up0 = vertex2_1->x;
			else if(index == 1) up0 = vertex2_1->y;
			else if(index == 2) up0 = vertex2_1->z;

			F32 up1;

			if(index == 0) up1 = vertex2_2->x;
			else if(index == 1) up1 = vertex2_2->y;
			else if(index == 2) up1 = vertex2_2->z;

			F32 up2;

			if(index == 0) up2 = vertex2_3->x;
			else if(index == 1) up2 = vertex2_3->y;
			else if(index == 2) up2 = vertex2_3->z;

			F32 a = 0.0f;
			F32 b = 0.0f;
			F32 c = 0.0f;
			F32 x0 = 0.0f;
			F32 x1 = 0.0f;

			if(computeIntervals(vp0, vp1, vp2, dv0, dv1, dv2, dv0dv1, dv0dv2, a, b, c, x0, x1))
			{
				if(coplanar(n1, vertex1_1, vertex1_2, vertex1_3, vertex2_1, vertex2_2, vertex2_3) == true) return true;
				else
				{
					delete e1;
					delete e2;
					delete n1;
					delete n2;
					delete dd;

					continue;
				}
			}

			F32 d = 0.0f;
			F32 e = 0.0f;
			F32 f = 0.0f;
			F32 y0 = 0.0f;
			F32 y1 = 0.0f;

			if(computeIntervals(up0, up1, up2, du0, du1, du2, du0du1, du0du2, d, e, f, y0, y1))
			{
				if(coplanar(n1, vertex1_1, vertex1_2, vertex1_3, vertex2_1, vertex2_2, vertex2_3) == true) return true;
				else
				{
					delete e1;
					delete e2;
					delete n1;
					delete n2;
					delete dd;

					continue;
				}
			}

			F32 xx = x0 * x1;
			F32 yy = y0 * y1;
			F32 xxyy = xx * yy;

			F32 tmp = a * xxyy;

			Vector2 *isect1 = new Vector2();

			isect1->x = tmp + b * x1 * yy;
			isect1->y = tmp + c * x0 * yy;

			Vector2 *isect2 = new Vector2();

			isect2->x = tmp + e * xx * y1;
			isect2->y = tmp + f * xx * y0;

			if(isect1->x > isect1->y)
			{
				F32 c = isect1->x;

				isect1->x = isect1->y;
				isect1->y = c;
			}

			if(isect2->x > isect2->y)
			{
				F32 c = isect2->x;

				isect2->x = isect2->y;
				isect2->y = c;
			}

			if(!(isect1->y < isect2->x || isect2->y < isect1->x) == true) return true;

			delete e1;
			delete e2;
			delete n1;
			delete n2;
			delete dd;
			delete isect1;
			delete isect2;
		}
	}

	for(U64 i = 0; i < vertices1.size(); i++) delete vertices1.at(i);
	for(U64 i = 0; i < vertices2.size(); i++) delete vertices2.at(i);

	vertices1.clear();
	vertices2.clear();

	return false;
}

bool MeshColliderComponent::computeIntervals(F32 vv0, F32 vv1, F32 vv2,
		F32 d0, F32 d1, F32 d2, F32 d0d1, F32 d0d2,
		F32 &a, F32 &b, F32 &c, F32 &x0, F32 &x1)
{
	if(d0d1 > 0.0f)
	{
		a = vv2;
		b = (vv0 - vv2) * d2;
		c = (vv1 - vv2) * d2;
		x0 = d2 - d0;
		x1 = d2 - d1;
	}
	else if(d0d1 > 0.0f)
	{
		a = vv1;
		b = (vv0 - vv1) * d1;
		c = (vv2 - vv1) * d1;
		x0 = d1 - d0;
		x1 = d1 - d2;
	}
	else if(d1 * d2 > 0.0f || d0 != 0.0f)
	{
		a = vv0;
		b = (vv1 - vv0) * d0;
		c = (vv2 - vv0) * d0;
		x0 = d0 - d1;
		x1 = d0 - d2;
	}
	else if(d1 != 0.0f)
	{
		a = vv1;
		b = (vv0 - vv1) * d1;
		c = (vv2 * vv1) * d1;
		x0 = d1 - d0;
		x1 = d1 - d2;
	}
	else if(d2 != 0.0f)
	{
		a = vv2;
		b = (vv0 - vv2) * d2;
		c = (vv1 - vv2) * d2;
		x0 = d2 - d0;
		x1 = d2 - d1;
	}
	else return true;

	return false;
}

bool MeshColliderComponent::coplanar(Vector3 *n, Vector3 *v0, Vector3 *v1, Vector3 *v2,
		Vector3 *u0, Vector3 *u1, Vector3 *u2)
{
	F32 a[3];

	S16 i0, i1;

	a[0] = abs(n->x);
	a[1] = abs(n->y);
	a[2] = abs(n->z);

	if(a[0] > a[1])
	{
		if(a[0] > a[2])
		{
			i0 = 1;
			i1 = 2;
		}
		else
		{
			i0 = 0;
			i1 = 1;
		}
	}
	else
	{
		if(a[2] > a[1])
		{
			i0 = 0;
			i1 = 1;
		}
		else
		{
			i0 = 0;
			i1 = 2;
		}
	}

	if(edgeAgainstTriEdges(v0, v1, u0, u1, u2, i0, i1)) return true;
	if(edgeAgainstTriEdges(v1, v2, u0, u1, u2, i0, i1)) return true;
	if(edgeAgainstTriEdges(v2, v0, u0, u1, u2, i0, i1)) return true;

	if(pointInTri(v0, u0, u1, u2, i0, i1)) return true;
	if(pointInTri(u0, v0, v1, v2, i0, i1)) return true;

	return false;
}

bool MeshColliderComponent::edgeAgainstTriEdges(Vector3 *v0, Vector3 *v1, Vector3 *u0, Vector3 *u1, Vector3 *u2, S16 i0, S16 i1)
{
	if(edgeTest(v0, v1, u0, u1, i0, i1)) return true;
	if(edgeTest(v0, v1, u1, u2, i0, i1)) return true;
	if(edgeTest(v0, v1, u2, u0, i0, i1)) return true;

	return false;
}

bool MeshColliderComponent::pointInTri(Vector3 *v0, Vector3 *u0, Vector3 *u1, Vector3 *u2, S16 i0, S16 i1)
{
	F32 a;

	if(i1 == 0) a = u1->x - u0->x;
	else if(i1 == 1) a = u1->y - u0->y;
	else if(i1 == 2) a = u1->z - u0->z;

	F32 b;

	if(i0 == 0) b = -(u1->x - u0->x);
	else if(i0 == 1) b = -(u1->y - u0->y);
	else if(i0 == 2) b = -(u1->z - u0->z);

	F32 c;

	F32 result1;

	if(i0 == 0) result1 = u0->x;
	else if(i0 == 1) result1 = u0->y;
	else if(i0 == 2) result1 = u0->z;

	F32 result2;

	if(i1 == 0) result2 = u0->x;
	else if(i1 == 1) result2 = u0->y;
	else if(i1 == 2) result2 = u0->z;

	c = -a * result1 - b * result2;

	F32 result3;

	if(i0 == 0) result3 = v0->x;
	else if(i0 == 1) result3 = v0->y;
	else if(i0 == 2) result3 = v0->z;

	F32 result4;

	if(i1 == 0) result4 = v0->x;
	else if(i1 == 1) result4 = v0->y;
	else if(i1 == 2) result4 = v0->z;

	F32 d0 = a * result3 + b * result4 + c;

	if(i1 == 0) a = u2->x - u1->x;
	else if(i1 == 1) a = u2->y - u1->y;
	else if(i1 == 2) a = u2->z - u1->z;

	if(i0 == 0) b = -(u2->x - u1->x);
	else if(i0 == 1) b = -(u2->y - u1->y);
	else if(i0 == 2) b = -(u2->z - u1->z);

	if(i0 == 0) result1 = u1->x;
	else if(i0 == 1) result1 = u1->y;
	else if(i0 == 2) result1 = u1->z;

	if(i1 == 0) result2 = u1->x;
	else if(i1 == 1) result2 = u1->y;
	else if(i1 == 2) result2 = u1->z;

	c = -a * result1 - b * result2;

	F32 d1 = a * result3 + b * result4 + c;

	//SECOND

	if(i1 == 0) a = u0->x - u2->x;
	else if(i1 == 1) a = u0->y - u2->y;
	else if(i1 == 2) a = u0->z - u2->z;

	if(i0 == 0) b = -(u0->x - u2->x);
	else if(i0 == 1) b = -(u0->y - u2->y);
	else if(i0 == 2) b = -(u0->z - u2->z);

	if(i0 == 0) result1 = u2->x;
	else if(i0 == 1) result1 = u2->y;
	else if(i0 == 2) result1 = u2->z;

	if(i1 == 0) result2 = u2->x;
	else if(i1 == 1) result2 = u2->y;
	else if(i1 == 2) result2 = u2->z;

	c = -a * result1 - b * result2;

	F32 d2 = a * result3 + b * result4 + c;

	if(d0 * d1 > 0.0f) if(d0 * d2 > 0.0f) return true;

	return false;
}

bool MeshColliderComponent::edgeTest(Vector3 *v0, Vector3 *v1, Vector3 *u0, Vector3 *u1, S16 i0, S16 i1)
{
	F32 ax;

	if(i0 == 0) ax = v1->x - v0->x;
	else if(i0 == 1) ax = v1->y - v0->y;
	else if(i0 == 2) ax = v1->z - v0->z;

	F32 ay;

	if(i1 == 0) ay = v1->x - v0->x;
	else if(i1 == 1) ay = v1->y - v0->y;
	else if(i1 == 2) ay = v1->z - v0->z;

	F32 bx;

	if(i0 == 0) bx = u0->x - u1->x;
	else if(i0 == 1) bx = u0->y - u1->y;
	else if(i0 == 2) bx = u0->z - u1->z;

	F32 by;

	if(i1 == 0) by = u0->x - u1->x;
	else if(i1 == 1) by = u0->y - u1->y;
	else if(i1 == 2) by = u0->z - u1->z;

	F32 cx;

	if(i0 == 0) cx = v0->x - u0->x;
	else if(i0 == 1) cx = v0->y - u0->y;
	else if(i0 == 2) cx = v0->z - u0->z;

	F32 cy;

	if(i1 == 0) cx = v0->x - u0->x;
	else if(i1 == 1) cx = v0->y - u0->y;
	else if(i1 == 2) cx = v0->z - u0->z;

	F32 f = ay * bx - ax * by;
	F32 d = by * cx - bx * cy;

	if((f > 0 && d >= 0 && d <= f) || (f > 0 && d <= 0 && d >= f))
	{
		F32 el = ax * cy - ay * cx;

		if(f > 0)
		{
			if(el >= 0 && el <= f) return true;
		}
		else if(el <= 0 && el >= f) return true;
	}

	return false;
}
