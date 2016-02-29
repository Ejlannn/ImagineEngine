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

#include "freeCameraMovement.h"

void FreeCameraMovement::onInit()
{
	font1 = FilePath::getFileFromGamePath("resources\\font\\font1.ttf");
	shotSound = FilePath::getFileFromGamePath("resources\\audio\\shot.wav");
}

void FreeCameraMovement::onUpdate()
{
	Scene *scene = Game::getCurrentScene();

	scene->camera->yaw = MouseInput::getMousePosition(MouseAxis::X) / 10;
	scene->camera->pitch = MouseInput::getMousePosition(MouseAxis::Y) / 10;

	TransformComponent *cameraTransform = (TransformComponent*) scene->camera->getEntity()->getComponent("TransformComponent");

	F32 speed = 0.002f;

	if(MouseInput::isPressed(MouseButton::BUTTON_LEFT)) if(!Audio::isSoundEffectPlaying(1)) Audio::playSoundEffect(shotSound, 1);

	if(Audio::isSoundEffectPlaying(1)) UIText::renderSimpleText("Sound effect is playing", font1, 12, Vector2(1.0f, 1.0f));

	if(KeyboardInput::isPressed(KeyboardKey::KEY_ESCAPE)) Game::exit(); //Exits game on ESC

	if(KeyboardInput::isPressed(KeyboardKey::KEY_W))
	{
		F32 pitchRad = MathUtil::degToRad(-scene->camera->pitch);
		F32 yawRad = MathUtil::degToRad(-scene->camera->yaw);

		cameraTransform->position->x -= Time::getDeltaTime() * speed * sinf(yawRad) * cosf(pitchRad);
		cameraTransform->position->y -= Time::getDeltaTime() * speed * -sinf(pitchRad);
		cameraTransform->position->z -= Time::getDeltaTime() * speed * cosf(yawRad) * cosf(pitchRad);
	}
	if(KeyboardInput::isPressed(KeyboardKey::KEY_S))
	{
		F32 pitchRad = MathUtil::degToRad(-scene->camera->pitch);
		F32 yawRad = MathUtil::degToRad(-scene->camera->yaw);

		cameraTransform->position->x += Time::getDeltaTime() * speed * sinf(yawRad) * cosf(pitchRad);
		cameraTransform->position->y += Time::getDeltaTime() * speed * -sinf(pitchRad);
		cameraTransform->position->z += Time::getDeltaTime() * speed * cosf(yawRad) * cosf(pitchRad);
	}
	if(KeyboardInput::isPressed(KeyboardKey::KEY_D))
	{
		F32 pitchRad = MathUtil::degToRad(scene->camera->pitch);
		F32 yawRad = MathUtil::degToRad(scene->camera->yaw);

		cameraTransform->position->z += Time::getDeltaTime() * speed * sinf(yawRad) * cosf(pitchRad);
		cameraTransform->position->y += Time::getDeltaTime() * speed * -sinf(pitchRad);
		cameraTransform->position->x += Time::getDeltaTime() * speed * cosf(yawRad) * cosf(pitchRad);
	}
	if(KeyboardInput::isPressed(KeyboardKey::KEY_A))
	{
		F32 pitchRad = MathUtil::degToRad(scene->camera->pitch);
		F32 yawRad = MathUtil::degToRad(scene->camera->yaw);

		cameraTransform->position->z -= Time::getDeltaTime() * speed * sinf(yawRad) * cosf(pitchRad);
		cameraTransform->position->y -= Time::getDeltaTime() * speed * -sinf(pitchRad);
		cameraTransform->position->x -= Time::getDeltaTime() * speed * cosf(yawRad) * cosf(pitchRad);
	}
}

void FreeCameraMovement::onDestroy() {}
