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
	Entity::Init();

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
	Entity::Update();

	for(int i = 0; i < currentNum; i++)
	{
		if(sceneObjects)
		{
			sceneObjects[i]->Update();
		}
	}
}

Entity* dfScene::GetEntityByIndex(int i)
{
	return sceneObjects[i];
}

void dfScene::RemoveSceneObject(Entity* sceneObj)
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
	BoxCollider* colliderA = (BoxCollider*)dfComponentMap[typeid(BoxCollider)];
	while(colliderA != 0)
	{
		BoxCollider* colliderB = (BoxCollider*)dfComponentMap[typeid(BoxCollider)];
		while(colliderB != 0)
		{
			if(colliderA != colliderB)
			{
				colliderA->BoxBoxCollision(*colliderA, *colliderB);
			}

			colliderB = (BoxCollider*)colliderB->nextInList;
		}
		colliderA = (BoxCollider*)colliderA->nextInList;
	}
}