#pragma once

#include "../Components/DFComponent.h"
#include "../Core/STDUNC.h"
#include "../Core/DFCman.h"

class Entity
{
public:
	Entity(void);
	virtual ~Entity(void);

	virtual void Init();
	virtual void Update();

	// TODO: replace temporary max with a dynamic array solution
	static const int maxComponents = 20;
	int numComponents;
	dfComponent* components[maxComponents];
	
	void RegisterComponent(dfComponent* c);
	dfComponent* GetComponentByName(char* name);
	template<class T> T* GetComponent()
	{
		T* classInstance = NULL; 
		for(int i = 0; i < numComponents; i++)
		{
			// todo: if this dynamic cast fails, it's really hard to debug. Have it check first
			classInstance = dynamic_cast<T*>(components[i]);
			if(classInstance)
			{
				return classInstance;
			}
		}
		return classInstance;
	}
};
