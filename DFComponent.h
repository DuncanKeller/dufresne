#pragma once
class dfComponent
{
public:
	dfComponent(void);
	~dfComponent(void);

	virtual void Init();
	virtual void Update();

	char* name;
};

