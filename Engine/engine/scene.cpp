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

#include "scene.h"

#include "../graphics/lightProcessor.h"

Scene::Scene()
{
	backgroundColor = new Color3();
	ambientLightColor = new Color3(1.0f);
	camera = NULL;
	skybox = NULL;
	fogDensity = 0.0f;
	fogGradient = 1.5f;
}

void Scene::addEntity(Entity *entity)
{
	if(entity == NULL) return;
	if(entity->parent != NULL) return;

	for(U16 i = 0; i < entities.size(); i++)
	{
		if(entities.at(i)->getID() == entity->getID()) return;
	}

	entities.push_back(entity);
}

void Scene::removeEntity(Entity *entity)
{
	if(entity == NULL) return;

	for(U16 i = 0; i < entities.size(); i++)
	{
		if(entities.at(i)->getID() == entity->getID()) entities.erase(entities.begin() + i);
	}
}

Entity *Scene::getEntityByName(std::string name)
{
	Entity *entity = NULL;

	for(U16 i = 0; i < entities.size(); i++)
	{
		if(entities.at(i)->name == name) entity = entities.at(i);
	}

	return entity;
}

Entity *Scene::getEntityByID(U32 id)
{
	Entity *entity = NULL;

	for(U16 i = 0; i < entities.size(); i++)
	{
		if(entities.at(i)->getID() == id) entity = entities.at(i);
	}

	return entity;
}

std::vector<Entity*> Scene::getEntitiesWithName(std::string name)
{
	std::vector<Entity*> entity;

	for(U16 i = 0; i < entities.size(); i++)
	{
		if(entities.at(i)->name == name) entity.push_back(entities.at(i));
	}

	return entity;
}

std::vector<Entity*> Scene::getEntitiesWithTag(std::string tag)
{
	std::vector<Entity*> entity;

	for(U16 i = 0; i < entities.size(); i++)
	{
		if(entities.at(i)->tag == tag) entity.push_back(entities.at(i));
	}

	return entity;
}

void Scene::initialize()
{
	for(U32 i = 0; i < entities.size(); i++)
	{
		if(entities.at(i)->children.size() > 0)
		{
			initializeChildren(entities.at(i)->children);
		}

		if(entities.at(i)->hasComponent("ScriptComponent"))
		{
			ScriptComponent *scriptComponent = (ScriptComponent*) entities.at(i)->getComponent("ScriptComponent");

			if(scriptComponent->scripts.size() > 0)
			{
				scriptComponent->initialize();
			}
		}
	}
}

void Scene::update()
{
	LightProcessor::clear();

	for(U32 i = 0; i < entities.size(); i++)
	{
		if(entities.at(i)->children.size() > 0)
		{
			updateChildren(entities.at(i)->children);
		}

		if(entities.at(i)->hasComponent("ScriptComponent"))
		{
			ScriptComponent *scriptComponent = (ScriptComponent*) entities.at(i)->getComponent("ScriptComponent");

			if(scriptComponent->scripts.size() > 0)
			{
				scriptComponent->update();
			}
		}

		if(entities.at(i)->hasComponent("LightComponent"))
		{
			LightComponent *lightComponent = (LightComponent*) entities.at(i)->getComponent("LightComponent");

			if(lightComponent->light != NULL)
			{
				lightComponent->light->entity = entities.at(i);
				LightProcessor::addLightSource(lightComponent->light);
			}
		}
	}
}

void Scene::destroy()
{
	for(U32 i = 0; i < entities.size(); i++)
	{
		if(entities.at(i)->children.size() > 0)
		{
			destroyChildren(entities.at(i)->children);
		}

		if(entities.at(i)->hasComponent("ScriptComponent"))
		{
			ScriptComponent *scriptComponent = (ScriptComponent*) entities.at(i)->getComponent("ScriptComponent");

			if(scriptComponent->scripts.size() > 0)
			{
				scriptComponent->destroy();
			}
		}
	}
}

void Scene::initializeChildren(std::vector<Entity*> children)
{
	for(U32 i = 0; i < children.size(); i++)
	{
		if(children.at(i)->hasComponent("ScriptComponent"))
		{
			ScriptComponent *scriptComponent = (ScriptComponent*) children.at(i)->getComponent("ScriptComponent");

			if(scriptComponent->scripts.size() > 0)
			{
				scriptComponent->initialize();
			}
		}

		if(children.at(i)->children.size() > 0) initializeChildren(children.at(i)->children);
	}
}

void Scene::updateChildren(std::vector<Entity*> children)
{
	for(U32 i = 0; i < children.size(); i++)
	{
		if(children.at(i)->hasComponent("ScriptComponent"))
		{
			ScriptComponent *scriptComponent = (ScriptComponent*) children.at(i)->getComponent("ScriptComponent");

			if(scriptComponent->scripts.size() > 0)
			{
				scriptComponent->update();
			}
		}

		if(children.at(i)->hasComponent("LightComponent"))
		{
			LightComponent *lightComponent = (LightComponent*) children.at(i)->getComponent("LightComponent");

			if(lightComponent->light != NULL) LightProcessor::addLightSource(lightComponent->light);
		}

		if(children.at(i)->children.size() > 0) updateChildren(children.at(i)->children);
	}
}

void Scene::destroyChildren(std::vector<Entity*> children)
{
	for(U32 i = 0; i < children.size(); i++)
	{
		if(children.at(i)->hasComponent("ScriptComponent"))
		{
			ScriptComponent *scriptComponent = (ScriptComponent*) children.at(i)->getComponent("ScriptComponent");

			if(scriptComponent->scripts.size() > 0)
			{
				scriptComponent->destroy();
			}
		}

		if(children.at(i)->children.size() > 0) destroyChildren(children.at(i)->children);
	}
}
