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

#include <sstream>
#include "script.h"
#include "game/game.h"
#include "../graphics/lightProcessor.h"

Scene::Scene()
{
	backgroundColor = Color3();
	ambientLightColor = Color3(1.0f);
	camera = nullptr;
	skybox = nullptr;
	fogDensity = 0.0f;
	fogGradient = 1.5f;
}

Scene::~Scene() {}

void Scene::addEntity(Entity *entity)
{
	if(entity == nullptr)
	{
		std::ostringstream id1;
		id1 << entity->getID();

		Game::getLogger()->warning("Cannot add Entity to Scene - Given Entity is NULL");
		return;
	}

	if(entity->parent != nullptr)
	{
		std::ostringstream id1;
		id1 << entity->getID();

		Game::getLogger()->warning("Cannot add Entity [Name: " + entity->name + " ID: " + id1.str() + "] to Scene - Given Entity has a parent");
		return;
	}

	for(U16 i = 0; i < entities.size(); i++)
	{
		if(entities.at(i)->getID() == entity->getID())
		{
			std::ostringstream id1;
			id1 << entity->getID();

			Game::getLogger()->warning("Cannot add Entity [Name: " + entity->name + " ID: " + id1.str() + "] to Scene - Given Entity has been already added to this Scene");
			return;
		}
	}

	entities.push_back(entity);
}

void Scene::removeEntity(Entity *entity)
{
	if(entity == nullptr)
	{
		std::ostringstream id1;
		id1 << entity->getID();

		Game::getLogger()->warning("Cannot remove Entity from Scene - Given Entity is NULL");
		return;
	}

	for(U16 i = 0; i < entities.size(); i++)
	{
		if(entities.at(i)->getID() == entity->getID())
		{
			entities.erase(entities.begin() + i);
			return;
		}
	}

	std::ostringstream id1;
	id1 << entity->getID();

	Game::getLogger()->warning("Cannot remove Entity [Name: " + entity->name + " ID: " + id1.str() + "] from Scene - Given Entity doesn't membership to this Scene");
	return;
}

Entity *Scene::getEntityByName(std::string name)
{
	for(U16 i = 0; i < entities.size(); i++) if(entities.at(i)->name == name) return entities.at(i);

	return nullptr;
}

Entity *Scene::getEntityByID(U32 id)
{
	for(U16 i = 0; i < entities.size(); i++)
		if(entities.at(i)->getID() == id) return entities.at(i);

	return nullptr;
}

std::vector<Entity*> Scene::getEntitiesWithName(std::string name)
{
	std::vector<Entity*> entity;

	for(U16 i = 0; i < entities.size(); i++) if(entities.at(i)->name == name) entity.push_back(entities.at(i));

	return entity;
}

std::vector<Entity*> Scene::getEntitiesWithTag(std::string tag)
{
	std::vector<Entity*> entity;

	for(U16 i = 0; i < entities.size(); i++) if(entities.at(i)->tag == tag) entity.push_back(entities.at(i));

	return entity;
}

void Scene::initialize()
{
	for(U32 i = 0; i < entities.size(); i++) initializeEntity(entities.at(i));
}

void Scene::update()
{
	LightProcessor::clear();

	for(U32 i = 0; i < entities.size(); i++) updateEntity(entities.at(i));
}

void Scene::destroy()
{
	for(U32 i = 0; i < entities.size(); i++) destroyEntity(entities.at(i));
}

void Scene::initializeEntity(Entity *entity)
{
	if(entity->children.size() > 0) for(U32 i = 0; i < entity->children.size(); i++) initializeEntity(entity->children.at(i));

	if(entity->hasComponent("MeshRendererComponent") && entity->hasComponent("MeshColliderComponent"))
	{
		MeshRendererComponent *meshRendererComponent = (MeshRendererComponent*) entity->getComponent("MeshRendererComponent");

		if(meshRendererComponent->model != nullptr)
		{
			TransformComponent *transformComponent = (TransformComponent*) entity->getComponent("TransformComponent");

			Matrix4 *transformationMatrix = TransformComponent::createTransformationMatrix(transformComponent);

			std::vector<Vector4*> processedVertices;

			for(U64 i = 0; i < meshRendererComponent->model->vertices.size(); i++)
			{
				Vector4 *vertex = new Vector4(meshRendererComponent->model->vertices.at(i)->x,
						meshRendererComponent->model->vertices.at(i)->y,
						meshRendererComponent->model->vertices.at(i)->z, 1.0);


				delete vertex;

				Vector4 *result = Vector4::transform(vertex, transformationMatrix);

				processedVertices.push_back(result);
			}

			delete transformationMatrix;

			MeshColliderComponent *meshColComponent = (MeshColliderComponent*) entity->getComponent("MeshColliderComponent");

			if(meshColComponent->obb[0] == nullptr) meshColComponent->createOOB(processedVertices);

			for(U64 i = 0; i < processedVertices.size(); i++) delete processedVertices.at(i);
		}
	}

	if(entity->hasComponent("ScriptComponent"))
	{
		ScriptComponent *scriptComponent = (ScriptComponent*) entity->getComponent("ScriptComponent");

		if(scriptComponent->scripts.size() > 0) scriptComponent->initialize();
	}
}

void Scene::updateEntity(Entity *entity)
{
	if(entity->children.size() > 0) for(U32 i = 0; i < entity->children.size(); i++) updateEntity(entity->children.at(i));

	if(entity->hasComponent("MeshRendererComponent") && entity->hasComponent("MeshColliderComponent"))
	{
		MeshRendererComponent *meshRendererComponent = (MeshRendererComponent*) entity->getComponent("MeshRendererComponent");

		if(meshRendererComponent->model != nullptr)
		{
			MeshColliderComponent *meshColComponent = (MeshColliderComponent*) entity->getComponent("MeshColliderComponent");

			if(meshColComponent->staticCollider == false)
			{
				TransformComponent *transformComponent = (TransformComponent*) entity->getComponent("TransformComponent");

				Matrix4 *transformationMatrix = TransformComponent::createTransformationMatrix(transformComponent);

				std::vector<Vector4*> processedVertices;

				for(U64 i = 0; i < meshRendererComponent->model->vertices.size(); i++)
				{
					Vector4 *vertex = new Vector4(meshRendererComponent->model->vertices.at(i)->x,
							meshRendererComponent->model->vertices.at(i)->y,
							meshRendererComponent->model->vertices.at(i)->z, 1.0);

					Vector4 *result = Vector4::transform(vertex, transformationMatrix);

					delete vertex;

					processedVertices.push_back(result);
				}

				delete transformationMatrix;

				MeshColliderComponent *meshColComponent = (MeshColliderComponent*) entity->getComponent("MeshColliderComponent");

				meshColComponent->createOOB(processedVertices);

				for(U64 i = 0; i < processedVertices.size(); i++) delete processedVertices.at(i);
			}
		}
	}
	if(entity->hasComponent("MeshRendererComponent") && entity->hasComponent("MeshColliderComponent") && entity->hasComponent("ScriptComponent"))
	{
		ScriptComponent *scriptComponent = (ScriptComponent*) entity->getComponent("ScriptComponent");

		MeshRendererComponent *meshRendererComponent1 = (MeshRendererComponent*) entity->getComponent("MeshRendererComponent");

		if(meshRendererComponent1->model != nullptr && scriptComponent->scripts.size() > 0)
		{
			for(U32 j = 0; j < entities.size(); j++)
			{
				if(entities.at(j)->hasComponent("MeshRendererComponent") && entities.at(j)->hasComponent("MeshColliderComponent") && entities.at(j)->getID() != entity->getID())
				{
					MeshRendererComponent *meshRendererComponent2 = (MeshRendererComponent*) entities.at(j)->getComponent("MeshRendererComponent");

					TransformComponent *transformComponent1 = (TransformComponent*) entity->getComponent("TransformComponent");

					Matrix4 *transformationMatrix1 = TransformComponent::createTransformationMatrix(transformComponent1);

					TransformComponent *transformComponent2 = (TransformComponent*) entities.at(j)->getComponent("TransformComponent");

					Matrix4 *transformationMatrix2 = TransformComponent::createTransformationMatrix(transformComponent2);

					std::vector<Vector4*> processedVertices1;

					for(U64 k = 0; k < meshRendererComponent1->model->vertices.size(); k++)
					{
						Vector4 *vertex = new Vector4(meshRendererComponent1->model->vertices.at(k)->x,
								meshRendererComponent1->model->vertices.at(k)->y,
								meshRendererComponent1->model->vertices.at(k)->z, 1.0);

						delete vertex;

						Vector4 *result = Vector4::transform(vertex, transformationMatrix1);

						processedVertices1.push_back(result);
					}

					std::vector<Vector4*> processedVertices2;

					for(U64 k = 0; k < meshRendererComponent2->model->vertices.size(); k++)
					{
						Vector4 *vertex = new Vector4(meshRendererComponent2->model->vertices.at(k)->x,
								meshRendererComponent2->model->vertices.at(k)->y,
								meshRendererComponent2->model->vertices.at(k)->z, 1.0);

						delete vertex;

						Vector4 *result = Vector4::transform(vertex, transformationMatrix2);

						processedVertices2.push_back(result);
					}

					MeshColliderComponent *meshCol1 = (MeshColliderComponent*) entity->getComponent("MeshColliderComponent");
					MeshColliderComponent *meshCol2 = (MeshColliderComponent*) entities.at(j)->getComponent("MeshColliderComponent");

					if(MeshColliderComponent::areColliding(meshCol1->obb, meshCol2->obb, processedVertices1, processedVertices2))
					{
						for(U16 m = 0; m < scriptComponent->scripts.size(); m++)
						{
							Collision *collision = new Collision(entities.at(j));
							scriptComponent->scripts.at(m)->onCollision(collision);
							delete collision;
						}
					}

					delete transformationMatrix1;
					delete transformationMatrix2;

					for(U64 i = 0; i < processedVertices1.size(); i++)
					{
						delete processedVertices1.at(i);
					}

					for(U64 i = 0; i < processedVertices2.size(); i++)
					{
						delete processedVertices2.at(i);
					}
				}
			}
		}
	}

	if(entity->hasComponent("ScriptComponent"))
	{
		ScriptComponent *scriptComponent = (ScriptComponent*) entity->getComponent("ScriptComponent");

		if(scriptComponent->scripts.size() > 0)
		{
			scriptComponent->update();
		}
	}

	if(entity->hasComponent("LightComponent"))
	{
		LightComponent *lightComponent = (LightComponent*) entity->getComponent("LightComponent");

		if(lightComponent->light != nullptr)
		{
			lightComponent->light->entity = entity;
			LightProcessor::addLightSource(lightComponent->light);
		}
	}

	if(entity->hasComponent("MaterialComponent"))
	{
		MaterialComponent *materialComponent = (MaterialComponent*) entity->getComponent("MaterialComponent");

		if(materialComponent->material != nullptr && materialComponent->material->sprite != nullptr && materialComponent->material->texture == nullptr)
			if(materialComponent->material->sprite->currentLayer != nullptr) materialComponent->material->sprite->currentLayer->update();
	}
}

void Scene::destroyEntity(Entity *entity)
{
	if(entity->children.size() > 0) for(U32 i = 0; i < entity->children.size(); i++) destroyEntity(entity->children.at(i));

	if(entity->hasComponent("ScriptComponent"))
	{
		ScriptComponent *scriptComponent = (ScriptComponent*) entity->getComponent("ScriptComponent");

		if(scriptComponent->scripts.size() > 0) scriptComponent->destroy();
	}
}
