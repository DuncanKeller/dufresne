#pragma once
#include "../entity/entity.h"
#include "../Components/Transform.h"
#include "../Components/Renderer.h"

class duiElement :
	public Entity
{
public:
	duiElement(void);
	virtual ~duiElement(void);

	virtual void Init();
	virtual void Update();

	Transform tf;
	Renderer render;

	void SetFocus(bool val);
	void OnFocus();
	void OnClick();
	
	duiElement* topLink;
	duiElement* bottomLink;
	duiElement* leftLink;
	duiElement* rightLink;

private:
	bool isFocused;
	bool startsWithFocus;
};

