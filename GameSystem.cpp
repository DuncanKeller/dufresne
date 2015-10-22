#include "GameSystem.h"


GameSystem::GameSystem(void)
{
	numComponents = 0;
	for(int i = 0; i < numComponents; i++)
	{
		components[i] = NULL;
	}
}


GameSystem::~GameSystem(void)
{
}

void GameSystem::Init()
{
	
}

void GameSystem::Update()
{
	dfAssert(numComponents < maxComponents);
	for(int i = 0; i < numComponents; i++)
	{
		(*components[i]).Update();
	}
}

void GameSystem::RegisterComponent(dfComponent* newComponent)
{
	if(numComponents < maxComponents - 1)
	{
		newComponent->gameSystem = this;
		components[numComponents] = newComponent;
		(*components[numComponents]).Init();
		numComponents++;
	}
	else
	{
		dfLog("max components reached... need to make dyanmic array, or better component storage solution");
	}
}

dfComponent* GameSystem::GetComponentByName(char* name)
{
	for(int i = 0; i < numComponents; i++)
	{
		if(dfStrCmp((*components[i]).name, name))
		{
			return components[i];
		}
	}
	return NULL;
}