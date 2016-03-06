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

#include "entity.h"

#include <sstream>
#include "game/game.h"

static U32 entityID = 0;

Entity::Entity()
{
	name = "Entity";
	tag = "";
	id = entityID;
	parent = nullptr;
	entityID++;

	components.push_back(new TransformComponent());
}

Entity::Entity(TransformComponent *transform)
{
	name = "Entity";
	tag = "";
	id = entityID;
	parent = nullptr;
	entityID++;

	if(transform->entity == nullptr) components.push_back(transform);
	else components.push_back(new TransformComponent);
}

Entity::Entity(std::string name)
{
	this->name = name;
	tag = "";
	id = entityID;
	parent = nullptr;
	entityID++;

	components.push_back(new TransformComponent());
}

Entity::Entity(std::string name, TransformComponent *transform)
{
	this->name = name;
	tag = "";
	id = entityID;
	parent = nullptr;
	entityID++;

	if(transform->entity == nullptr) components.push_back(transform);
	else components.push_back(new TransformComponent);
}

Entity::~Entity()
{
	components.clear();
	children.clear();
}

void Entity::addComponent(ComponentBase *component)
{
	if(component == nullptr)
	{
		std::ostringstream id1;
		id1 << id;

		Game::getLogger()->warning("Cannot add component to Entity [Name: " + name + " ID: " + id1.str() + "] - Given component is NULL");
		return;
	}

	if(component->entity != nullptr)
	{
		std::ostringstream id1;
		id1 << id;

		Game::getLogger()->warning("Cannot add component with name " + component->getName() + "to Entity [Name: " + name + " ID: " + id1.str() + "] - Given component has been already added somewhere");
		return;
	}

	if(component->name == "MeshColliderComponent") if(hasComponent("BoxColliderComponent")) return;
	if(component->name == "BoxColliderComponent") if(hasComponent("MeshColliderComponent")) return;

	for(U16 i = 0; i < components.size(); i++)
	{
		if(components.at(i)->name == component->name)
		{
			std::ostringstream id1;
			id1 << id;

			Game::getLogger()->warning("Cannot add component with name " + component->getName() + "to Entity [Name: " + name + " ID: " + id1.str() + "] - Given component has been already added to this Entity");
			return;
		}
	}

	component->entity = this;
	components.push_back(component);
}

void Entity::removeComponent(ComponentBase *component)
{
	if(component == nullptr)
	{
		std::ostringstream id1;
		id1 << id;

		Game::getLogger()->warning("Cannot remove component from Entity [Name: " + name + " ID: " + id1.str() + "] - Given component is NULL");
		return;
	}

	if(component->entity == nullptr || component->entity->getID() != this->getID())
	{
		std::ostringstream id1;
		id1 << id;

		Game::getLogger()->warning("Cannot remove component with name " + component->getName() + " from Entity [Name: " + name + " ID: " + id1.str() + "] - Given component has been added to different Entity");
		return;
	}

	for(U16 i = 0; i < components.size(); i++)
	{
		if(components.at(i)->name == component->name)
		{
			component->entity = nullptr;
			components.erase(components.begin() + i);
			return;
		}
	}

	std::ostringstream id1;
	id1 << id;

	Game::getLogger()->warning("Cannot remove component with name " + component->getName() + " from Entity [Name: " + name + " ID: " + id1.str() + "] - Given component doesn't membership to this Entity");
	return;
}

ComponentBase *Entity::getComponent(std::string name)
{
	for(U16 i = 0; i < components.size(); i++)
	{
		if(components.at(i)->name == name) return components.at(i);
	}

	std::ostringstream id1;
	id1 << id;

	Game::getLogger()->warning("Given component with name " + name + " doesn't membership to this Entity [Name: " + this->name + " ID: " + id1.str() + "]");
	return nullptr;
}

bool Entity::hasComponent(std::string name)
{
	for(U16 i = 0; i < components.size(); i++)
	{
		if(components.at(i)->name == name) return true;
	}

	return false;
}

void Entity::addChild(Entity *entity)
{
	if(entity == nullptr)
	{
		std::ostringstream id1;
		id1 << id;

		Game::getLogger()->warning("Cannot add child Entity to parent Entity [Name: " + name + " ID: " + id1.str() + "] - given child Entity is NULL");
		return;
	}

	if(entity->parent != nullptr)
	{
		std::ostringstream id1;
		id1 << id;

		std::ostringstream id2;
		id2 << entity->getID();

		Game::getLogger()->warning("Cannot add child Entity [Name: " + entity->name + " ID: " + id2.str() + "] to parent Entity [Name: " + name + " ID: " + id1.str() + "] - given child Entity already has a parent Entity");
		return;
	}

	if(children.size() != 0)
	{
		for(U16 i = 0; i < children.size(); i++)
		{
			if(children.at(i)->getID() == entity->getID())
			{
				std::ostringstream id1;
				id1 << id;

				std::ostringstream id2;
				id2 << entity->getID();

				Game::getLogger()->warning("Cannot add child Entity [Name: " + entity->name + " ID: " + id2.str() + "] to parent Entity [Name: " + name + " ID: " + id1.str() + "] - given child Entity has been already added to this parent Entity");
				return;
			}
		}
	}

	entity->parent = this;
	children.push_back(entity);
}

void Entity::removeChild(Entity *entity)
{
	if(entity == nullptr)
	{
		std::ostringstream id1;
		id1 << id;

		Game::getLogger()->warning("Cannot remove child Entity from parent Entity [Name: " + name + " ID: " + id1.str() + "] - given child Entity is NULL");
		return;
	}

	if(entity->parent != this)
	{
		std::ostringstream id1;
		id1 << id;

		std::ostringstream id2;
		id2 << entity->getID();

		Game::getLogger()->warning("Cannot remove child Entity [Name: " + entity->name + " ID: " + id2.str() + "] from parent Entity [Name: " + name + " ID: " + id1.str() + "] - given child Entity has different parent Entity");
		return;
	}

	for(U16 i = 0; i < children.size(); i++)
	{
		if(children.at(i)->getID() == entity->getID())
		{
			entity->parent = nullptr;
			children.erase(children.begin() + i);
			return;
		}
	}

	std::ostringstream id1;
	id1 << id;

	std::ostringstream id2;
	id2 << entity->getID();

	Game::getLogger()->warning("Cannot remove child Entity [Name: " + entity->name + " ID: " + id2.str() + "] from parent Entity [Name: " + name + " ID: " + id1.str() + "] - given child Entity doesn't membership to this parent Entity");
	return;
}

U32 Entity::getID()
{
	return id;
}

Entity *Entity::getParent()
{
	return parent;
}

Vector3 Entity::getPreviousPosition()
{
	return previousPosition;
}
