#pragma once
#include "Entity.h"
#include "../Components/Transform.h"
#include "../Components/Renderer.h"
#include "../Components/BoxCollider.h"

class dfTile :
	public Entity
{
public:
	dfTile(void);
	virtual ~dfTile(void);

	virtual void Init();
	virtual void Update();

	virtual void InterpretProperty(const char* name, const char* value);
	
	virtual void AddCollision(Collider*);

	Transform tf;
	Renderer render;
	std::vector<Collider*> colliders;
};

