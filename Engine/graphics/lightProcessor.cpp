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
#include "../engine/light/light.h"

std::vector<Light*> lightSources;

void LightProcessor::addLightSource(Light *light)
{
	lightSources.push_back(light);
}

void LightProcessor::clear()
{
	lightSources.clear();
}

std::vector<Light*> LightProcessor::getLightSourcesForEntity(std::vector<Vector4*> vertices)
{
	std::vector<Light*> lightSourcesForEntity;

	Light *tempLight[4];

	tempLight[0] = NULL;
	tempLight[1] = NULL;
	tempLight[2] = NULL;
	tempLight[3] = NULL;

	for(U16 i = 0; i < lightSources.size(); i++)
	{
		if(lightSources.at(i)->type == "DirectionalLight")
		{
			tempLight[3] = tempLight[2];
			tempLight[2] = tempLight[1];
			tempLight[1] = tempLight[0];
			tempLight[0] = lightSources.at(i);
		}
		else if(lightSources.at(i)->type == "PointLight")
		{
			for(U32 j = 0; j < vertices.size(); j++)
			{
				TransformComponent *transformComponent = (TransformComponent*) lightSources.at(i)->entity->getComponent("TransformComponent");

				F32 distance = Vector4::distance(vertices.at(j), new Vector4(transformComponent->position, 1.0f));

				PointLight *pointLight = (PointLight*) lightSources.at(i);

				if(distance <= pointLight->range)
				{
					tempLight[4] = tempLight[3];
					tempLight[3] = tempLight[2];
					tempLight[2] = tempLight[1];
					tempLight[1] = lightSources.at(i);
					break;
				}
			}
		}
		else if(lightSources.at(i)->type == "SpotLight")
		{
			for(U32 j = 0; j < vertices.size(); j++)
			{
				//TODO
			}
		}
	}

	for(U16 i = 0; i < 4; i++)
	{
		if(tempLight[i] != NULL) lightSourcesForEntity.push_back(tempLight[i]);
		else lightSourcesForEntity.push_back(NULL);
	}

	return lightSourcesForEntity;
}
