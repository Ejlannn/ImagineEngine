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

#ifndef _IE_GRAPHICS_DEVICE_H_
#define _IE_GRAPHICS_DEVICE_H_

#include "../engine/scene.h"

class Game;
class UIText;
class BaseShader;
class SkyboxShader;
class UIShader;
class UIElement;

class GraphicsDevice
{
	friend class Game;
	friend class UIText;

private:
	static BaseShader *getBaseShader();
	static SkyboxShader *getSkyboxShader();
	static UIShader *getUIShader();

	static void init();
	static void render(Scene *scene);
	static void renderEntity(Entity *entity, MeshRendererComponent *mesh);
	static void renderSkybox(SkyboxAsset *skybox);
	static void renderUIElement(UIElement *element);
	static void startBaseShader(Entity *entity, Scene *scene);
	static void stopBaseShader();
	static void startSkyboxShader(Scene *scene);
	static void stopSkyboxShader();
	static void startUIShader();
	static void stopUIShader();
	//static void render(Scene *scene);
	//static void renderChildren(std::vector<Entity*> children, TransformComponent *parentTransform, Scene *scene);
	//static void renderElements(MeshRendererComponent *meshRendererComponent, bool textured);
	static void addTextToRender(const std::string &message, FilePath *fontFile, S16 size, Vector2 *position);
};

#endif
