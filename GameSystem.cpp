#include "GameSystem.h"


GameSystem::GameSystem(void)
{
	numComponents = 0;
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
		components[i].Update();
	}
}

void GameSystem::RegisterComponent(DFComponent newComponent)
{
	if(numComponents < maxComponents - 1)
	{
		components[++numComponents] = newComponent;
		components[numComponents].Init();
	}
	else
	{
		dfLog("max components reached... need to make dyanmic array, or better component storage solution");
	}
}
/*
TODO replace componenet system to use pointers so I can return null
DFComponent GameSystem::GetComponent(char* name)
{
	for(int i = 0; i < numComponents; i++)
	{
		if(dfStrCmp(components[i].name, name))
		{
			return components[i];
		}
	}
	return 0;
}
*/