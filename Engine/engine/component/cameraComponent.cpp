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

#include "cameraComponent.h"

#include "../entity.h"
#include "../../window/window.h"

CameraComponent::CameraComponent() : ComponentBase("CameraComponent")
{
	nearPlane = 0.1f;
	farPlane = 1000.0f;
	fov = 70.0f;

	yaw = 0.0f;
	pitch = 0.0f;
}

CameraComponent::~CameraComponent()
{
	delete &nearPlane;
	delete &farPlane;
	delete &fov;

	delete &yaw;
	delete &pitch;
}

Matrix4 *CameraComponent::createProjectionMatrix(CameraComponent *camera)
{
	Matrix4 *projectionMatrix = new Matrix4();

	F32 aspectRatio = (F32) Window::getWidth() / (F32) Window::getHeight();
    F32 y_scale = ((1.0f / tanf(MathUtil::degToRad(camera->fov / 2.0f))) * aspectRatio);
    F32 x_scale = y_scale / aspectRatio;
    F32 frustum_length = camera->farPlane - camera->nearPlane;

    projectionMatrix->m00 = x_scale;
    projectionMatrix->m11 = y_scale;
    projectionMatrix->m22 = -((camera->farPlane + camera->nearPlane) / frustum_length);
    projectionMatrix->m23 = -1;
    projectionMatrix->m32 = -((2 * camera->nearPlane * camera->farPlane) / frustum_length);
    projectionMatrix->m33 = 0;

    return projectionMatrix;
}

Matrix4 *CameraComponent::create2DOrthoProjectionMatrix()
{
	Matrix4 *projectionMatrix = new Matrix4();

	F32 left = 0.0f;
	F32 right = Window::getWidth();
	F32 bottom = Window::getHeight();
	F32 top = 0.0f;
	F32 near = -1.0f;
	F32 far = 1.0f;

	F32 xO = 2.0f / (right - left);
	F32 yO = 2.0f / (top - bottom);
	F32 zO = -2.0f / (far - near);

	F32 tx = -(right + left) / (right - left);
	F32 ty = -(top + bottom) / (top - bottom);
	F32 tz = -(far + near) / (far - near);

	projectionMatrix->m00 = xO;
	projectionMatrix->m10 = 0.0f;
	projectionMatrix->m20 = 0.0f;
	projectionMatrix->m30 = 0.0f;
	projectionMatrix->m01 = 0.0f;
	projectionMatrix->m11 = yO;
	projectionMatrix->m21 = 0.0f;
	projectionMatrix->m31 = 0.0f;
	projectionMatrix->m02 = 0.0f;
	projectionMatrix->m12 = 0.0f;
	projectionMatrix->m22 = zO;
	projectionMatrix->m32 = 0.0f;
	projectionMatrix->m03 = tx;
	projectionMatrix->m13 = ty;
	projectionMatrix->m23 = tz;
	projectionMatrix->m33 = 1.0f;

	return projectionMatrix;
}

Matrix4 *CameraComponent::createViewMatrix(CameraComponent *camera)
{
	Matrix4 *viewMatrix = new Matrix4();
	viewMatrix->setIdentity();

	viewMatrix->rotate(new Vector3(1.0f, 0.0f, 0.0f), MathUtil::degToRad(camera->pitch));
	viewMatrix->rotate(new Vector3(0.0f, 1.0f, 0.0f), MathUtil::degToRad(camera->yaw));

	TransformComponent *transformComponent = (TransformComponent*) camera->entity->getComponent("TransformComponent");

	Vector3 *negativeCam = new Vector3(-transformComponent->position->x, -transformComponent->position->y, -transformComponent->position->z);

	viewMatrix->translate(negativeCam);

	return viewMatrix;
}
