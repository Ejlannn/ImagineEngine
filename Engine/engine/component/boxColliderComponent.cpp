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
	rotate = false;
	scale = false;
	staticCollider = true;
}

BoxColliderComponent::BoxColliderComponent(F32 size) : ComponentBase("BoxColliderComponent")
{
	this->size = size;
	rotate = false;
	scale = false;
	staticCollider = true;
}

void BoxColliderComponent::create(Matrix4 *transformationMatrix)
{
	for(U16 i = 0; i < 8; i++) if(obb[i] != nullptr) delete obb[i];

	delete modelAsset;

	if(size < 0.0f) size = 1.0f;

	F32 sizeDiv = size / 2.0f;

	Vector4 *obb1 = new Vector4(Vector3(-sizeDiv, sizeDiv, sizeDiv), 0.0f);
	Vector4 *obb2 = new Vector4(Vector3(sizeDiv, sizeDiv, sizeDiv), 0.0f);
	Vector4 *obb3 = new Vector4(Vector3(-sizeDiv, sizeDiv, -sizeDiv), 0.0f);
	Vector4 *obb4 = new Vector4(Vector3(sizeDiv, sizeDiv, -sizeDiv), 0.0f);
	Vector4 *obb5 = new Vector4(Vector3(-sizeDiv, -sizeDiv, sizeDiv), 0.0f);
	Vector4 *obb6 = new Vector4(Vector3(sizeDiv, -sizeDiv, sizeDiv), 0.0f);
	Vector4 *obb7 = new Vector4(Vector3(-sizeDiv, -sizeDiv, -sizeDiv), 0.0f);
	Vector4 *obb8 = new Vector4(Vector3(sizeDiv, -sizeDiv, -sizeDiv), 0.0f);

	obb1->transform(transformationMatrix);
	obb2->transform(transformationMatrix);
	obb3->transform(transformationMatrix);
	obb4->transform(transformationMatrix);
	obb5->transform(transformationMatrix);
	obb6->transform(transformationMatrix);
	obb7->transform(transformationMatrix);
	obb8->transform(transformationMatrix);

	obb[0] = new Vector3(obb1->x, obb1->y, obb1->z);
	obb[1] = new Vector3(obb2->x, obb2->y, obb2->z);
	obb[2] = new Vector3(obb3->x, obb3->y, obb3->z);
	obb[3] = new Vector3(obb4->x, obb4->y, obb4->z);
	obb[4] = new Vector3(obb5->x, obb5->y, obb5->z);
	obb[5] = new Vector3(obb6->x, obb6->y, obb6->z);
	obb[6] = new Vector3(obb7->x, obb7->y, obb7->z);
	obb[7] = new Vector3(obb8->x, obb8->y, obb8->z);

	Vector4 *pos1 = new Vector4(-sizeDiv, -sizeDiv, sizeDiv, 0.0f);
	Vector4 *pos2 = new Vector4(sizeDiv, -sizeDiv, sizeDiv, 0.0f);
	Vector4 *pos3 = new Vector4(-sizeDiv, sizeDiv, sizeDiv, 0.0f);
	Vector4 *pos4 = new Vector4(sizeDiv, sizeDiv, sizeDiv, 0.0f);
	Vector4 *pos5 = new Vector4(-sizeDiv, sizeDiv, -sizeDiv, 0.0f);
	Vector4 *pos6 = new Vector4(sizeDiv, sizeDiv, -sizeDiv, 0.0f);
	Vector4 *pos7 = new Vector4(-sizeDiv, -sizeDiv, -sizeDiv, 0.0f);
	Vector4 *pos8 = new Vector4(sizeDiv, -sizeDiv, -sizeDiv, 0.0f);

	pos1->transform(transformationMatrix);
	pos2->transform(transformationMatrix);
	pos3->transform(transformationMatrix);
	pos4->transform(transformationMatrix);
	pos5->transform(transformationMatrix);
	pos6->transform(transformationMatrix);
	pos7->transform(transformationMatrix);
	pos8->transform(transformationMatrix);

	modelAsset = new ModelAsset();

	modelAsset->vertices.push_back(new Vector3(pos1->x, pos1->y, pos1->z));
	modelAsset->vertices.push_back(new Vector3(pos2->x, pos2->y, pos2->z));
	modelAsset->vertices.push_back(new Vector3(pos3->x, pos3->y, pos3->z));
	modelAsset->vertices.push_back(new Vector3(pos4->x, pos4->y, pos4->z));
	modelAsset->vertices.push_back(new Vector3(pos5->x, pos5->y, pos5->z));
	modelAsset->vertices.push_back(new Vector3(pos6->x, pos6->y, pos6->z));
	modelAsset->vertices.push_back(new Vector3(pos7->x, pos7->y, pos7->z));
	modelAsset->vertices.push_back(new Vector3(pos8->x, pos8->y, pos8->z));

	delete obb1;
	delete obb2;
	delete obb3;
	delete obb4;
	delete obb5;
	delete obb6;
	delete obb7;
	delete obb8;

	delete pos1;
	delete pos2;
	delete pos3;
	delete pos4;
	delete pos5;
	delete pos6;
	delete pos7;
	delete pos8;
}
