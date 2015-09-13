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
	DFComponent components[maxComponents];
	
	void RegisterComponent(DFComponent c);
	DFComponent GetComponent(char* name);
};
