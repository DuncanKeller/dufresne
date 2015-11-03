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

void dfScene::DoCollision()
{
	for(int ai = 0; ai < currentNum; ai++)
	{
		if(sceneObjects[ai])
		{
			BoxCollider* colliderA = sceneObjects[ai]->GetComponent<BoxCollider>();
			if(colliderA)
			{
				for(int bi = 0; bi < currentNum; bi++)
				{
					if(sceneObjects[bi])
					{
						BoxCollider* colliderB = sceneObjects[bi]->GetComponent<BoxCollider>();
						if(colliderB && colliderA != colliderB)
						{
							colliderA->BoxBoxCollision(*colliderA, *colliderB);
						}
					}
				}
			}
		}
	}
}