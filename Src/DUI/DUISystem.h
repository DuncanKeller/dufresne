#pragma once
#include "../entity/gamesystem.h"
#include "../System/Input.h"
#include "duiElement.h"

class DUISystem :
	public GameSystem
{
public:
	DUISystem(void);
	virtual ~DUISystem(void);
	
	virtual void Init();
	virtual void Update();

	void SetFocus(duiElement* newElement);

private:
	duiElement* currentFocusedElement;
};

