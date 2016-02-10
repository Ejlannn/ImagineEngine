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

#include "transformComponent.h"

TransformComponent::TransformComponent() : ComponentBase("TransformComponent")
{
	position = new Vector3();
	rotation = new Vector3();
	scale = new Vector3(1.0f);
}

TransformComponent::TransformComponent(Vector3 *position) : ComponentBase("TransformComponent")
{
	this->position = position;
	rotation = new Vector3();
	scale = new Vector3(1.0f);
}

TransformComponent::TransformComponent(Vector3 *position, Vector3 *rotation, Vector3 *scale) : ComponentBase("TransformComponent")
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

TransformComponent::~TransformComponent()
{
	delete position;
	delete rotation;
	delete scale;
}

Matrix4 *TransformComponent::createTransformationMatrix(TransformComponent *component)
{
	return createTransformationMatrix(component->position, component->rotation, component->scale);
}

Matrix4 *TransformComponent::createTransformationMatrix(Vector3 *translation, Vector3 *rotation, Vector3 *scale)
{
	Matrix4 *transformationMatrix = new Matrix4();
	transformationMatrix->setIdentity();

	transformationMatrix->translate(translation);
	transformationMatrix->rotate(new Vector3(1.0f, 0.0f, 0.0f), MathUtil::degToRad(rotation->x));
	transformationMatrix->rotate(new Vector3(0.0f, 1.0f, 0.0f), MathUtil::degToRad(rotation->y));
	transformationMatrix->rotate(new Vector3(0.0f, 0.0f, 1.0f), MathUtil::degToRad(rotation->z));
	transformationMatrix->scale(scale);

	return transformationMatrix;
}
