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
class UINShader;
class UIElement;

class GraphicsDevice
{
	friend class Game;
	friend class UIText;

public:
	static void setSamplesSize(U16 samples);

private:
	static BaseShader *getBaseShader();
	static SkyboxShader *getSkyboxShader();
	static UIShader *getUIShader();
	static UINShader *getUINShader();

	static void prepare3D();
	static void clear();
	static void clear(Color3 color);
	static void init();
	static void destroy();
	static void render(Scene *scene);
	static void renderEntity(Entity *entity, MeshRendererComponent *mesh);
	static void renderSkybox(SkyboxAsset *skybox, Scene *scene);
	static void renderUIElement(UIElement element);
	static void renderConsole();
	static void startBaseShader(Entity *entity, Scene *scene);
	static void stopBaseShader();
	static void startSkyboxShader(Scene *scene, U16 face);
	static void stopSkyboxShader();
	static void startUIShader();
	static void stopUIShader();
	static void startUINShader(Color3 color);
	static void stopUINShader();
	static void addTextToRender(const std::string &message, FilePath *fontFile, S16 size, Vector2 position);
	static void addTextToRender(const std::string &message, FilePath *fontFile, S16 size, Vector2 position, Color3 color);
};

#endif
