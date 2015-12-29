#pragma once

class Entity;

class dfComponent
{
public:
	dfComponent(void);
	~dfComponent(void);

	virtual void Init();
	virtual void Update();

	char* name;
	Entity* entity;

	dfComponent* nextInList;
};

