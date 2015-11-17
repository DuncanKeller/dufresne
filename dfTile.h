#pragma once
#include "gamesystem.h"
#include "Transform.h"
#include "Renderer.h"
#include "BoxCollider.h"

class dfTile :
	public GameSystem
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

