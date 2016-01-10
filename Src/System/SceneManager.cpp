#include "SceneManager.h"

SceneManager sceneMan;

SceneManager::SceneManager(void)
{
	// create default scene
	dfScene* defaultScene = new dfScene();
	defaultScene->name = "defaultScene";
	sceneList.push_back(defaultScene);
	currentScene = sceneList[0];
	LoadScene(currentScene);
}


SceneManager::~SceneManager(void)
{
}

dfScene* SceneManager::CreateScene(std::string name)
{
	dfScene* newScene = new dfScene();
	newScene->name = name;
	sceneList.push_back(newScene);
	return newScene;
}

void SceneManager::Init()
{
	GameSystem::Init();

	renderer.Init();
}

void SceneManager::Update()
{
	GameSystem::Update();

	if(currentScene != NULL)
	{
		currentScene->Update();
		currentScene->DoCollision();
	}

	renderer.Update();
	renderer.RenderLoop(currentScene);
}

void SceneManager::LoadScene(dfScene* scene)
{
	UnloadScene(currentScene);
	currentScene = scene;
	currentScene->Init();
	currentScene->SetupScene();
}

void SceneManager::LoadScene(std::string name)
{
	for(int i = 0; i < sceneList.size(); i++)
	{
		if(dfStrCmp(sceneList[i]->name, name))
		{
			LoadScene(sceneList[i]);
			return;
		}
	}

	dfError("No scene exists with that name"); 
}

void SceneManager::UnloadScene(dfScene* scene)
{
	if(scene)
		scene->RemoveAllSceneObjects();
}

void SceneManager::RemoveSceneObject(Entity* system)
{
	if(currentScene)
	{
		currentScene->RemoveSceneObject(system);
	}
	else
	{
		dfError("NO SCENE TO REMOVE OBJECT FROM");
	}
}
