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

#include "exampleGame.h"

/* Script Includes */
#include "scripts/freeCameraMovement.h"

int main()
{
	Game *exampleGame = new ExampleGame();
	exampleGame->run();

	return 0;
}

void ExampleGame::initializeGame()
{
	/*
	 * W, A, S, D to move camera
	 * ESC to exit
	 */

	/* Scenes */
	Scene *scene1 = new Scene();

	/* scene1 Settings */
	scene1->backgroundColor = new Color3(0.2f, 0.2f, 0.2f);
	scene1->fogDensity = 0.05f;
	scene1->fogGradient = 1.4f;

	/* Pathes */
	std::string exePath;
	exePath += FilePath::getGamePath();

	std::string skyFolder;
	std::string texturesFolder;
	std::string modelsFolder;

	skyFolder += exePath;
	skyFolder += "resources\\skybox\\";

	texturesFolder += exePath;
	texturesFolder += "resources\\texture\\";

	modelsFolder += exePath;
	modelsFolder += "resources\\model\\";

	/* Skybox */
	FilePath *pathes[6];

	pathes[0] = new FilePath(skyFolder + "right2.png");
	pathes[1] = new FilePath(skyFolder + "left2.png");
	pathes[2] = new FilePath(skyFolder + "up2.png");
	pathes[3] = new FilePath(skyFolder + "down2.png");
	pathes[4] = new FilePath(skyFolder + "back2.png");
	pathes[5] = new FilePath(skyFolder + "front2.png");

	SkyboxAsset *skybox = new SkyboxAsset(pathes);
	scene1->skybox = skybox; //Apply skybox

	/* Scripts */
	FreeCameraMovement *freeCameraMovement = new FreeCameraMovement();

	/* Entities */
	//----CAMERA----//
	Entity *cameraEntity = new Entity("Camera"); //Important camera entity

	CameraComponent *cameraComponent = new CameraComponent();
	//cameraComponent->fov = 60.0f;
	cameraEntity->addComponent(cameraComponent);

	scene1->camera = cameraComponent; //Sets our camera as current camera

	TransformComponent *cameraTransform = (TransformComponent*) cameraEntity->getComponent("TransformComponent");
	cameraTransform->position->z = 5.0f;

	ScriptComponent *scriptComponent = new ScriptComponent();
	scriptComponent->addScript(freeCameraMovement);
	cameraEntity->addComponent(scriptComponent);

	//----CUBE----//
	Entity *cubeEntity = new Entity("Cube");

	MeshRendererComponent *meshComponent = new MeshRendererComponent();
	meshComponent->model = ModelLoader::loadOBJModel(new FilePath(modelsFolder + "cube.obj")); //Loads cube.obj model
	cubeEntity->addComponent(meshComponent);

	//----CAT----//
	Entity *catEntity = new Entity("Cat");

	MeshRendererComponent *meshComponent2 = new MeshRendererComponent();
	meshComponent2->model = ModelLoader::loadOBJModel(new FilePath(modelsFolder + "cat.obj")); //Loads cat.obj model
	catEntity->addComponent(meshComponent2);

	MaterialComponent *materialComponent = new MaterialComponent();
	materialComponent->material->texture = new TextureAsset(new FilePath(texturesFolder + "cat.png")); //Loads texture for cat
	catEntity->addComponent(materialComponent);

	TransformComponent *catTransform = (TransformComponent*) catEntity->getComponent("TransformComponent");
	catTransform->position->y = 1.0f;
	catTransform->position->x = 0.5f;
	//catTransform->rotation->x = 50.0f;

	/* Apply Entities */
	scene1->addEntity(cameraEntity);
	scene1->addEntity(cubeEntity);
	cubeEntity->addChildren(catEntity);
	//scene1->addEntity(catEntity);

	/* Apply Scene */
	setCurrentScene(scene1);
}
