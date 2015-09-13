#pragma once
class DFComponent
{
public:
	DFComponent(void);
	~DFComponent(void);

	virtual void Init();
	virtual void Update();

	char* name;
};

