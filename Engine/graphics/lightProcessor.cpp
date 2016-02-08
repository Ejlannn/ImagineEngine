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

#include "lightProcessor.h"

std::vector<Light*> lightSources;

void LightProcessor::addLightSource(Light *light)
{
	lightSources.push_back(light);
}

void LightProcessor::clear()
{
	lightSources.clear();
}

std::vector<Light*> LightProcessor::getLightSourcesForEntity(Entity *entity)
{
	/*std::vector<Light*> lights;

	Light *tempLight[4];

	tempLight[1] = NULL;
	tempLight[2] = NULL;
	tempLight[3] = NULL;
	tempLight[4] = NULL;

	for(U16 i = 0; i < lightSources.size(); i++)
	{
		if(lightSources.at(i)->type == "DirectionalLight")
		{
			tempLight[4] = tempLight[3];
			tempLight[3] = tempLight[2];
			tempLight[2] = tempLight[1];
			tempLight[1] = lightSources.at(i);
		}
		else
		{
			TransformComponent *transform = (TransformComponent*) entity->getComponent("TransformComponent");
			TransformComponent *lightTransform = (TransformComponent*) lightSources.at(i)->entity->getComponent("TransformComponent");
			TransformComponent *light2Transform = (TransformComponent*) lightSources.at(i)->entity->getComponent("TransformComponent");

			F32 distance = Vector3::distance(transform->position, lightTransform->position);
			F32 distance2 = Vector3::distance(transform->position, light2Transform->position);

			if(distance < distance2)
			{
				tempLight[4] = tempLight[3];
				tempLight[3] = tempLight[2];
				tempLight[2] = tempLight[1];
				tempLight[1] = lightSources.at(i);
			}
		}
	}

	return lights;*/

	return NULL;
}
