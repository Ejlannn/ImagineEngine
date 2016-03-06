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
	name = "Scene";
}

Scene::Scene(std::string name)
{
	backgroundColor = Color3();
	ambientLightColor = Color3(1.0f);
	camera = nullptr;
	skybox = nullptr;
	fogDensity = 0.0f;
	fogGradient = 1.5f;
	this->name = name;
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

	if(entity->hasComponent("ScriptComponent"))
	{
		ScriptComponent *scriptComponent = (ScriptComponent*) entity->getComponent("ScriptComponent");

		if(scriptComponent->scripts.size() > 0) scriptComponent->initialize();
	}

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

	if(entity->hasComponent("BoxColliderComponent"))
	{
		TransformComponent *transformComponent = (TransformComponent*) entity->getComponent("TransformComponent");

		BoxColliderComponent *boxColliderComponent = (BoxColliderComponent*) entity->getComponent("BoxColliderComponent");

		Vector3 *rotation = new Vector3();

		bool delRot = false;

		if(boxColliderComponent->rotate)
		{
			delete rotation;
			rotation = transformComponent->rotation;
		}
		else delRot = true;

		Vector3 *scale = new Vector3(1.0f);

		bool delScale;

		if(boxColliderComponent->scale)
		{
			delete scale;
			scale = transformComponent->scale;
		}
		else delScale = true;

		Matrix4 *transformationMat = TransformComponent::createTransformationMatrix(transformComponent->position, rotation, scale);

		boxColliderComponent->create(transformationMat);

		delete transformationMat;

		if(delRot) delete rotation;
		if(delScale) delete scale;
	}
}

void Scene::updateEntity(Entity *entity)
{
	if(entity->children.size() > 0) for(U32 i = 0; i < entity->children.size(); i++) updateEntity(entity->children.at(i));

	TransformComponent *transformComponent = (TransformComponent*) entity->getComponent("TransformComponent");

	entity->previousPosition.x = transformComponent->position->x;
	entity->previousPosition.y = transformComponent->position->y;
	entity->previousPosition.z = transformComponent->position->z;

	if(entity->hasComponent("ScriptComponent"))
	{
		ScriptComponent *scriptComponent = (ScriptComponent*) entity->getComponent("ScriptComponent");

		if(scriptComponent->scripts.size() > 0)
		{
			scriptComponent->update();
		}
	}

	if(entity->hasComponent("BoxColliderComponent"))
	{
		BoxColliderComponent *boxColliderComponent = (BoxColliderComponent*) entity->getComponent("BoxColliderComponent");

		if(boxColliderComponent->staticCollider == false)
		{
			Vector3 *rotation = new Vector3();

			bool delRot = false;

			if(boxColliderComponent->rotate)
			{
				delete rotation;
				rotation = transformComponent->rotation;
			}
			else delRot = true;

			Vector3 *scale = new Vector3(1.0f);

			bool delScale;

			if(boxColliderComponent->scale)
			{
				delete scale;
				scale = transformComponent->scale;
			}
			else delScale = true;

			Matrix4 *transformationMat = TransformComponent::createTransformationMatrix(transformComponent->position, rotation, scale);

			boxColliderComponent->create(transformationMat);

			delete transformationMat;

			if(delRot) delete rotation;
			if(delScale) delete scale;
		}
	}

	if(entity->hasComponent("MeshRendererComponent") && entity->hasComponent("MeshColliderComponent"))
	{
		MeshRendererComponent *meshRendererComponent = (MeshRendererComponent*) entity->getComponent("MeshRendererComponent");

		if(meshRendererComponent->model != nullptr)
		{
			MeshColliderComponent *meshColComponent = (MeshColliderComponent*) entity->getComponent("MeshColliderComponent");

			if(meshColComponent->staticCollider == false)
			{
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

					if(meshRendererComponent2->model == nullptr) continue;

					Matrix4 *transformationMatrix1 = TransformComponent::createTransformationMatrix(transformComponent);

					TransformComponent *transformComponent2 = (TransformComponent*) entities.at(j)->getComponent("TransformComponent");

					Matrix4 *transformationMatrix2 = TransformComponent::createTransformationMatrix(transformComponent2);

					MeshColliderComponent *meshCol1 = (MeshColliderComponent*) entity->getComponent("MeshColliderComponent");
					MeshColliderComponent *meshCol2 = (MeshColliderComponent*) entities.at(j)->getComponent("MeshColliderComponent");

					if(MeshColliderComponent::areColliding(meshCol1->obb, meshCol2->obb, meshRendererComponent1->model, meshRendererComponent2->model,
							transformationMatrix1, transformationMatrix2))
					{
						for(U16 m = 0; m < scriptComponent->scripts.size(); m++)
						{
							scriptComponent->scripts.at(m)->onCollision(Collision(entities.at(j)));
						}
					}

					delete transformationMatrix1;
					delete transformationMatrix2;
				}
				else if(entities.at(j)->hasComponent("BoxColliderComponent") && entities.at(j)->getID() != entity->getID())
				{
					BoxColliderComponent *boxColliderComponent2 = (BoxColliderComponent*) entities.at(j)->getComponent("BoxColliderComponent");

					Vector3 *pos = new Vector3();
					Vector3 *rot = new Vector3();
					Vector3 *scl = new Vector3(1.0f);

					Matrix4 *transformMat = TransformComponent::createTransformationMatrix(pos, rot, scl);

					delete pos;
					delete rot;
					delete scl;

					Matrix4 *transformationMatrix1 = TransformComponent::createTransformationMatrix(transformComponent);

					MeshColliderComponent *meshCol1 = (MeshColliderComponent*) entity->getComponent("MeshColliderComponent");

					if(MeshColliderComponent::areColliding(meshCol1->obb, boxColliderComponent2->obb,
							meshRendererComponent1->model, boxColliderComponent2->modelAsset,
							transformationMatrix1, transformMat))
					{
						for(U16 m = 0; m < scriptComponent->scripts.size(); m++)
						{
							scriptComponent->scripts.at(m)->onCollision(Collision(entities.at(j)));
						}
					}

					delete transformMat;
					delete transformationMatrix1;
				}
			}
		}
	}

	if(entity->hasComponent("BoxColliderComponent") && entity->hasComponent("ScriptComponent"))
	{
		ScriptComponent *scriptComponent = (ScriptComponent*) entity->getComponent("ScriptComponent");

		if(scriptComponent->scripts.size() > 0)
		{
			BoxColliderComponent *boxColliderComponent1 = (BoxColliderComponent*) entity->getComponent("BoxColliderComponent");

			for(U32 j = 0; j < entities.size(); j++)
			{
				if(entities.at(j)->hasComponent("BoxColliderComponent") && entities.at(j)->getID() != entity->getID())
				{
					BoxColliderComponent *boxColliderComponent2 = (BoxColliderComponent*) entities.at(j)->getComponent("BoxColliderComponent");

					Vector3 *pos = new Vector3();
					Vector3 *rot = new Vector3();
					Vector3 *scl = new Vector3(1.0f);

					Matrix4 *transformMat = TransformComponent::createTransformationMatrix(pos, rot, scl);

					delete pos;
					delete rot;
					delete scl;

					if(MeshColliderComponent::areColliding(boxColliderComponent1->obb, boxColliderComponent2->obb,
							boxColliderComponent1->modelAsset, boxColliderComponent2->modelAsset,
							transformMat, transformMat))
					{
						for(U16 m = 0; m < scriptComponent->scripts.size(); m++)
						{
							scriptComponent->scripts.at(m)->onCollision(Collision(entities.at(j)));
						}
					}

					delete transformMat;
				}
				else if(entities.at(j)->hasComponent("MeshRendererComponent") && entities.at(j)->hasComponent("MeshColliderComponent") && entities.at(j)->getID() != entity->getID())
				{
					MeshRendererComponent *meshRendererComponent2 = (MeshRendererComponent*) entities.at(j)->getComponent("MeshRendererComponent");

					if(meshRendererComponent2->model == nullptr) continue;

					Vector3 *pos = new Vector3();
					Vector3 *rot = new Vector3();
					Vector3 *scl = new Vector3(1.0f);

					Matrix4 *transformMat = TransformComponent::createTransformationMatrix(pos, rot, scl);

					delete pos;
					delete rot;
					delete scl;

					TransformComponent *transformComponent2 = (TransformComponent*) entities.at(j)->getComponent("TransformComponent");

					Matrix4 *transformationMatrix2 = TransformComponent::createTransformationMatrix(transformComponent2);

					MeshColliderComponent *meshCol2 = (MeshColliderComponent*) entities.at(j)->getComponent("MeshColliderComponent");

					if(MeshColliderComponent::areColliding(boxColliderComponent1->obb, meshCol2->obb, boxColliderComponent1->modelAsset, meshRendererComponent2->model,
							transformMat, transformationMatrix2))
					{
						for(U16 m = 0; m < scriptComponent->scripts.size(); m++)
						{
							scriptComponent->scripts.at(m)->onCollision(Collision(entities.at(j)));
						}
					}

					delete transformMat;
					delete transformationMatrix2;
				}
			}
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
