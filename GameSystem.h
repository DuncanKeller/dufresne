#pragma once

#include "DFComponent.h"
#include "STDUNC.h"

class GameSystem
{
public:
	GameSystem(void);
	virtual ~GameSystem(void);

	virtual void Init();
	virtual void Update();

	// TODO: replace temporary max with a dynamic array solution
	static const int maxComponents = 5;
	int numComponents;
	// major TODO
	// I'd rather not have an array of pointers, but I can't think of a way
	// to avoid object slicing otherwise. R Smtih can halp with ideas maybe
	dfComponent* components[maxComponents];
	
	void RegisterComponent(dfComponent* c);
	dfComponent* GetComponentByName(char* name);
	template<class T> T* GetComponent()
	{
		T* classInstance = NULL;
		for(int i = 0; i < numComponents; i++)
		{
			classInstance = (T*)(components[i]);
			if(classInstance)
			{
				return classInstance;
			}
		}
		return classInstance;
	}
};
