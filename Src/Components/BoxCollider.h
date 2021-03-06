#pragma once
#include "collider.h"
#include "../Core/dfBasic.h"

class BoxCollider :
	public Collider
{
public:
	BoxCollider(void);
	virtual ~BoxCollider(void);

	virtual void Init();
	virtual void Update();

	void BoxBoxCollision(BoxCollider &a, BoxCollider &b);

	Rect* collisionRect;
};

