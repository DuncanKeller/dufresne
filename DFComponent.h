#pragma once

class GameSystem;

class dfComponent
{
public:
	dfComponent(void);
	~dfComponent(void);

	virtual void Init();
	virtual void Update();

	char* name;
	GameSystem* gameSystem;
};

