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

#include <iostream>

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
	//bool obbResult = false;

	for(U16 i = 0; i < 8; i++)
	{
		Vector3 *currentOBBVertex = obb1[i];

		Vector3 *min = obb2[6];
		Vector3 *max = obb2[1];

		std::cout << "Checking" << std::endl;

		std::cout << currentOBBVertex->x << " " << currentOBBVertex->y << " " << currentOBBVertex->x << std::endl;

		if((currentOBBVertex->x >= min->x && currentOBBVertex->x <= max->x) && (currentOBBVertex->y >= min->y && currentOBBVertex->y <= max->y) && (currentOBBVertex->z >= min->z && currentOBBVertex->z <= max->z))
		{
			return true;
		}
	}

	return false;
}
