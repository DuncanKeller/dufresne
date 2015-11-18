#pragma once
#include "Entity.h"
#include "Transform.h"
#include "Renderer.h"
#include "BoxCollider.h"

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

