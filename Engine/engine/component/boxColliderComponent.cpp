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

#include "boxColliderComponent.h"

BoxColliderComponent::BoxColliderComponent() : ComponentBase("BoxColliderComponent")
{
	size = 1.0f;
	staticCollider = true;
	modelAsset = new ModelAsset();

	for(U16 i = 0; i < 8; i++) obb[i] = nullptr;
}

BoxColliderComponent::BoxColliderComponent(F32 size) : ComponentBase("BoxColliderComponent")
{
	this->size = size;
	staticCollider = true;
	modelAsset = new ModelAsset();

	for(U16 i = 0; i < 8; i++) obb[i] = nullptr;
}

BoxColliderComponent::~BoxColliderComponent()
{
	for(U16 i = 0; i < 8; i++) if(obb[i] != nullptr) delete obb[i];

	delete modelAsset;
}

void BoxColliderComponent::create(Vector3 *position)
{
	for(U16 i = 0; i < 8; i++) if(obb[i] != nullptr) delete obb[i];

	delete modelAsset;

	if(size < 0.0f) size = 1.0f;

	F32 sizeDiv = size / 2.0f;

	obb[0] = new Vector3(-sizeDiv + position->x, sizeDiv + position->y, sizeDiv + position->z);
	obb[1] = new Vector3(sizeDiv + position->x, sizeDiv + position->y, sizeDiv + position->z);
	obb[2] = new Vector3(-sizeDiv + position->x, sizeDiv + position->y, -sizeDiv + position->z);
	obb[3] = new Vector3(sizeDiv + position->x, sizeDiv + position->y, -sizeDiv + position->z);
	obb[4] = new Vector3(-sizeDiv + position->x, -sizeDiv + position->y, sizeDiv + position->z);
	obb[5] = new Vector3(sizeDiv + position->x, -sizeDiv + position->y, sizeDiv + position->z);
	obb[6] = new Vector3(-sizeDiv + position->x, -sizeDiv + position->y, -sizeDiv + position->z);
	obb[7] = new Vector3(sizeDiv + position->x, -sizeDiv + position->y, -sizeDiv + position->z);

	modelAsset = new ModelAsset();

	modelAsset->vertices.push_back(new Vector3(-sizeDiv + position->x, -sizeDiv + position->y, sizeDiv + position->z));
	modelAsset->vertices.push_back(new Vector3(sizeDiv + position->x, -sizeDiv + position->y, sizeDiv + position->z));
	modelAsset->vertices.push_back(new Vector3(-sizeDiv + position->x, sizeDiv + position->y, sizeDiv + position->z));
	modelAsset->vertices.push_back(new Vector3(sizeDiv + position->x, sizeDiv + position->y, sizeDiv + position->z));
	modelAsset->vertices.push_back(new Vector3(-sizeDiv + position->x, sizeDiv + position->y, -sizeDiv + position->z));
	modelAsset->vertices.push_back(new Vector3(sizeDiv + position->x, sizeDiv + position->y, -sizeDiv + position->z));
	modelAsset->vertices.push_back(new Vector3(-sizeDiv + position->x, -sizeDiv + position->y, -sizeDiv + position->z));
	modelAsset->vertices.push_back(new Vector3(sizeDiv + position->x, -sizeDiv + position->y, -sizeDiv + position->z));

	modelAsset->faces.push_back(new Face(1, 2, 3));
	modelAsset->faces.push_back(new Face(3, 2, 4));
	modelAsset->faces.push_back(new Face(3, 4, 5));
	modelAsset->faces.push_back(new Face(5, 4, 6));
	modelAsset->faces.push_back(new Face(5, 6, 7));
	modelAsset->faces.push_back(new Face(7, 6, 8));
	modelAsset->faces.push_back(new Face(7, 8, 1));
	modelAsset->faces.push_back(new Face(1, 8, 2));
	modelAsset->faces.push_back(new Face(2, 8, 4));
	modelAsset->faces.push_back(new Face(4, 8, 6));
	modelAsset->faces.push_back(new Face(7, 1, 5));
	modelAsset->faces.push_back(new Face(5, 1, 3));
}
