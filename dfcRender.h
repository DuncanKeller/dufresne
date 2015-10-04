#pragma once
#include "dfcomponent.h"
class dfcRender :
	public dfComponent
{
public:
	dfcRender(void);
	~dfcRender(void);

	virtual void Init();
	virtual void Update();
};

