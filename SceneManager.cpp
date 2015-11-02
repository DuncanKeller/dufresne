#include "SceneManager.h"

SceneManager sceneMan;

SceneManager::SceneManager(void)
{
	// create default scene
	dfScene defaultScene;
	defaultScene.name = "defaultScene";
	sceneList.push_back(defaultScene);
	currentScene = &sceneList[0];
	LoadScene(currentScene);
}


SceneManager::~SceneManager(void)
{
}

void SceneManager::Init()
{
	GameSystem::Init();

	renderer.Init();
}

void SceneManager::Update()
{
	GameSystem::Init();

	if(currentScene != NULL)
	{
		currentScene->Update();
	}

	renderer.Update();
	renderer.RenderLoop(currentScene);
}

void SceneManager::LoadScene(dfScene* scene)
{
	currentScene = scene;
	currentScene->Init();
}

void SceneManager::LoadScene(std::string name)
{
	for(int i = 0; i < sceneList.size(); i++)
	{
		if(dfStrCmp(sceneList[i].name, name))
		{
			LoadScene(&sceneList[i]);
			return;
		}
	}

	dfLog("No scene exists with that name"); // todo make dfLogWarning
}

void SceneManager::RemoveSceneObject(GameSystem* system)
{
	if(currentScene)
	{
		currentScene->RemoveSceneObject(system);
	}
	else
	{
		dfLog("NO SCENE TO REMOVE OBJECT FROM"); // todo make dfLogError
	}
}