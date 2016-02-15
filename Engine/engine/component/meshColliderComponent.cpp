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

MeshColliderComponent::MeshColliderComponent() : ComponentBase("MeshColliderComponent")
{
	staticCollider = true;

	for(U16 i = 0; i < 8; i++)
	{
		obb[i] = NULL;
	}
}

MeshColliderComponent::~MeshColliderComponent()
{
	delete &staticCollider;
}

void MeshColliderComponent::createOOB(std::vector<Vector4*> vertices)
{
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

bool MeshColliderComponent::areColliding(Vector3 *obb1[8], Vector3 *obb2[8], std::vector<Vector4*> vertices1, std::vector<Vector4*> vertices2)
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
	}

	if(obbResult == false) return false;
	else return true;

	U32 obbSiz = 0;

	for(U64 i = 0; i < vertices2.size(); i++)
	{
		Vector3 *min = obb2[6];
		Vector3 *max = obb2[1];
	}

	if(obbSiz == 0)
	{
		obbSiz = 1;

	}

	Vector3 *obbs[obbSiz][8];

	if(obbSiz == 1)
	{
		obbs[0][0] = obb2[0];
		obbs[0][1] = obb2[1];
		obbs[0][3] = obb2[2];
		obbs[0][2] = obb2[3];
		obbs[0][4] = obb2[4];
		obbs[0][5] = obb2[5];
		obbs[0][6] = obb2[6];
		obbs[0][7] = obb2[7];
	}

	for(U64 i = 0; i < vertices1.size(); i++)
	{
		for (U16 k = 0; k < obbSiz; k++)
		{
			for(U16 j = 0; j < 8; j++)
			{
				Vector3 *currentVertex = new Vector3(vertices1.at(i)->x, vertices1.at(i)->y, vertices1.at(i)->z);

				Vector3 *min = obbs[k][6];
				Vector3 *max = obbs[k][1];

				if((currentVertex->x >= min->x && currentVertex->x <= max->x) && (currentVertex->y >= min->y && currentVertex->y <= max->y) && (currentVertex->z >= min->z && currentVertex->z <= max->z))
				{
					return true;
				}
			}
		}
	}

	return false;
}
