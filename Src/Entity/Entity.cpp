#include "Entity.h"


Entity::Entity(void)
{
	numComponents = 0;
	for(int i = 0; i < numComponents; i++)
	{
		components[i] = NULL;
	}
}


Entity::~Entity(void)
{
}

void Entity::Init()
{
	
}

void Entity::Update()
{
	dfAssert(numComponents < maxComponents);
	for(int i = 0; i < numComponents; i++)
	{
		(*components[i]).Update();
	}
}

void Entity::RegisterComponent(dfComponent* newComponent)
{
	if(numComponents < maxComponents - 1)
	{
		AddComponentToMap(newComponent);
		newComponent->entity = this;
		components[numComponents] = newComponent;
		(*components[numComponents]).Init();
		numComponents++;
	}
	else
	{
		dfLog("max components reached... need to make dyanmic array, or better component storage solution");
	}
}

dfComponent* Entity::GetComponentByName(char* name)
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