#pragma once
#include "dfcomponent.h"
#include "../Core/dfBasic.h"
#include "../Core/STDUNC.h"
#include <vector>

#include "../System/AssetManager.h"
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

protected:
	Transform* tf;
	bool enabled;

};

