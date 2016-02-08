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

/* Scripts Include */
#include "freeCameraMovement.h"

int main()
{
	Game *exampleGame = new ExampleGame();
	exampleGame->run();
}

void ExampleGame::initializeGame()
{
	//W, A, S, D to move camera
	//ESC to exit


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

	/* Scripts */
	FreeCameraMovement *freeCameraScript = new FreeCameraMovement();

	/* Scene Init */
	Scene *scene1 = new Scene();
	scene1->backgroundColor = new Color3(0.1f, 0.5f, 1.0f);

	FilePath *pathes[6];

	pathes[0] = new FilePath(skyFolder + "right2.png");
	pathes[1] = new FilePath(skyFolder + "left2.png");
	pathes[2] = new FilePath(skyFolder + "up2.png");
	pathes[3] = new FilePath(skyFolder + "down2.png");
	pathes[4] = new FilePath(skyFolder + "back2.png");
	pathes[5] = new FilePath(skyFolder + "front2.png");

	SkyboxAsset *exampleSkybox = new SkyboxAsset(pathes);
	scene1->skybox = exampleSkybox;

	/* Entities Instance */
	Entity *camera = new Entity("Camera");
	CameraComponent *cameraCompo = new CameraComponent();
	camera->addComponent(cameraCompo);

	ScriptComponent *scriptComponent = new ScriptComponent();
	scriptComponent->addScript(freeCameraScript);
	camera->addComponent(scriptComponent);

	TransformComponent *cameraTransform = (TransformComponent*) camera->getComponent("TransformComponent");
	cameraTransform->position->z = 5.0f;

	Entity *entityCube = new Entity("Cube");
	Entity *entityCat = new Entity("Cat");

	MeshRendererComponent *cubeMesh = new MeshRendererComponent();
	cubeMesh->model = ModelLoader::loadOBJModel(new FilePath(modelsFolder + "cube.obj"));

	entityCube->addComponent(cubeMesh);

	MeshRendererComponent *catMesh = new MeshRendererComponent();
	catMesh->model = ModelLoader::loadOBJModel(new FilePath(modelsFolder + "cat.obj"));

	MaterialComponent *catMaterial = new MaterialComponent();
	catMaterial->material->texture = new TextureAsset(new FilePath(texturesFolder + "cat.png"));

	entityCat->addComponent(catMesh);
	entityCat->addComponent(catMaterial);

	TransformComponent *catTransform = (TransformComponent*) entityCat->getComponent("TransformComponent");
	catTransform->position->x = -3.0f;

	/* Apply Entities */
	scene1->addEntity(camera);
	scene1->addEntity(entityCube);
	scene1->addEntity(entityCat);

	/* Apply Scene */
	scene1->camera = cameraCompo;
	setCurrentScene(scene1);
}
