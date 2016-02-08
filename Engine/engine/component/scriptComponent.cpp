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

#include "scriptComponent.h"

#include "../script.h"

ScriptComponent::ScriptComponent() : ComponentBase("ScriptComponent") {}

ScriptComponent::~ScriptComponent()
{
	scripts.clear();
}

void ScriptComponent::addScript(Script *script)
{
	if(script == NULL) return;

	for(U32 i = 0; i < scripts.size(); i++)
	{
		if(scripts.at(i)->id == script->id) return;
	}

	scripts.push_back(script);
}

void ScriptComponent::removeScript(Script *script)
{
	if(script == NULL) return;

	for(U32 i = 0; i < scripts.size(); i++)
	{
		if(scripts.at(i)->id == script->id) scripts.erase(scripts.begin() + i);
	}
}

void ScriptComponent::initialize()
{
	for(U32 i = 0; i < scripts.size(); i++)
	{
		scripts.at(i)->entity = entity;
		scripts.at(i)->onInit();
		scripts.at(i)->entity = NULL;
	}
}

void ScriptComponent::update()
{
	for(U32 i = 0; i < scripts.size(); i++)
	{
		scripts.at(i)->entity = entity;
		scripts.at(i)->onUpdate();
		scripts.at(i)->entity = NULL;
	}
}

void ScriptComponent::destroy()
{
	for(U32 i = 0; i < scripts.size(); i++)
	{
		scripts.at(i)->entity = entity;
		scripts.at(i)->onDestroy();
		scripts.at(i)->entity = NULL;
	}
}
