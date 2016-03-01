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

#ifndef _IE_SCENE_H_
#define _IE_SCENE_H_

#include "entity.h"
#include "../assets/skybox/skyboxAsset.h"

class GraphicsDevice;
class Game;
class Event;

class Scene
{
	friend class GraphicsDevice;
	friend class Game;
	friend class Event;

public:
	Scene();

	~Scene();

	Color3 backgroundColor;
	Color3 ambientLightColor;
	CameraComponent *camera;
	SkyboxAsset *skybox;
	F32 fogDensity;
	F32 fogGradient;

	void addEntity(Entity *entity);
	void removeEntity(Entity *entity);
	Entity *getEntityByName(std::string name);
	Entity *getEntityByID(U32 id);
	std::vector<Entity*> getEntitiesWithName(std::string name);
	std::vector<Entity*> getEntitiesWithTag(std::string tag);

private:
	std::vector<Entity*> entities;

	void initialize();
	void update();
	void destroy();
	void initializeEntity(Entity *entity);
	void updateEntity(Entity *entity);
	void destroyEntity(Entity *entity);
};

#endif
