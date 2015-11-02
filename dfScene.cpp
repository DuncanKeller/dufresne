#include "dfScene.h"


dfScene::dfScene(void)
{
	currentNum = 0;
	for(int i = 0; i < MAX_OBJS_PER_SCENE; i++)
	{
		sceneObjects[i] = NULL;
	}
}


dfScene::~dfScene(void)
{
}


void dfScene::Init()
{
	GameSystem::Init();

	for(int i = 0; i < currentNum; i++)
	{
		if(sceneObjects)
		{
			sceneObjects[i]->Init();
		}
	}
}

void dfScene::Update()
{
	GameSystem::Update();

	for(int i = 0; i < currentNum; i++)
	{
		if(sceneObjects)
		{
			sceneObjects[i]->Update();
		}
	}
}

GameSystem* dfScene::GetGameSystemByIndex(int i)
{
	return sceneObjects[i];
}

void dfScene::RemoveSceneObject(GameSystem* sceneObj)
{
	for(int i = 0; i < currentNum; i++)
	{
		if(sceneObj == sceneObjects[i])
		{
			delete sceneObj;
			sceneObjects[i] = 0;
			freeSpots.push_back(i);
			break;
		}
	}
}