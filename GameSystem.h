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
	dfComponent components[maxComponents];
	
	void RegisterComponent(dfComponent c);
	dfComponent* GetComponent(char* name);
};
