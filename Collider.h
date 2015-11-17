#pragma once
#include "dfcomponent.h"
#include "dfBasic.h"
#include "STDUNC.h"
#include <vector>

#include "AssetManager.h"
#include "Transform.h"

class Collider :
	public dfComponent
{
public:
	Collider(void);
	virtual ~Collider(void);

	virtual void Init();
	virtual void Update();

	bool stationary;
	bool trigger;

	void SetEnabled(bool val);

	// todo add a pointer rectangle like Renderer does so that it can be changed by the user
	// to not point to the transform if desired

protected:
	Transform* tf;
	bool enabled;

};

