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

static U32 entityID = 0;

Entity::Entity()
{
	name = "Entity";
	tag = "";
	id = entityID;
	parent = NULL;
	entityID++;

	components.push_back(new TransformComponent());
}

Entity::Entity(TransformComponent *transform)
{
	name = "Entity";
	tag = "";
	id = entityID;
	parent = NULL;
	entityID++;

	if(transform->entity == NULL) components.push_back(transform);
	else components.push_back(new TransformComponent);
}

Entity::Entity(std::string name)
{
	this->name = name;
	tag = "";
	id = entityID;
	parent = NULL;
	entityID++;

	components.push_back(new TransformComponent());
}

Entity::Entity(std::string name, TransformComponent *transform)
{
	this->name = name;
	tag = "";
	id = entityID;
	parent = NULL;
	entityID++;

	if(transform->entity == NULL) components.push_back(transform);
	else components.push_back(new TransformComponent);
}

Entity::~Entity()
{
	components.clear();
	children.clear();
}

void Entity::addComponent(ComponentBase *component)
{
	if(component == NULL || component->entity != NULL) return;

	for(U16 i = 0; i < components.size(); i++)
	{
		if(components.at(i)->name == component->name) return;
	}

	component->entity = this;
	components.push_back(component);
}

void Entity::removeComponent(ComponentBase *component)
{
	if(component == NULL || component->entity == NULL || component->entity->getID() != this->getID()) return;

	for(U16 i = 0; i < components.size(); i++)
	{
		if(components.at(i)->name == component->name)
		{
			component->entity = NULL;
			components.erase(components.begin() + i);
			break;
		}
	}
}

ComponentBase *Entity::getComponent(std::string name)
{
	for(U16 i = 0; i < components.size(); i++)
	{
		if(components.at(i)->name == name) return components.at(i);
	}

	return NULL;
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
	if(entity == NULL || entity->parent != NULL) return;

	if(children.size() != 0)
	{
		for(U16 i = 0; i < children.size(); i++)
		{
			if(children.at(i)->getID() == entity->getID()) return;
		}
	}

	entity->parent = this;
	children.push_back(entity);
}

void Entity::removeChild(Entity *entity)
{
	if(entity == NULL || entity->parent != this) return;

	for(U16 i = 0; i < children.size(); i++)
	{
		if(children.at(i)->getID() == entity->getID())
		{
			entity->parent = NULL;
			children.erase(children.begin() + i);
			break;
		}
	}
}

U32 Entity::getID()
{
	return id;
}

Entity *Entity::getParent()
{
	return parent;
}
