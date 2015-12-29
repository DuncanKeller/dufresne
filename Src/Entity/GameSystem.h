#pragma once
class GameSystem
{
public:
	GameSystem(void);
	virtual ~GameSystem(void);

	virtual void Init();
	virtual void Update();

};

