#pragma once
#include "Entity.h"
#include "Renderer.h"
#include "Transform.h"
#include "MatMath.h"
#include "glew.h"
#include <GL/GL.h>
#include "dfBasic.h"
#include "AssetManager.h"
#include "SDL_image.h"
#include "Input.h"
#include "BoxCollider.h"
#include "STDUNC.h"
#include "dfAnimator.h"
#include "dfParticleSystem.h"

class TestEntity :
	public Entity
{
public:
	TestEntity(void);
	virtual ~TestEntity(void);
	virtual void Init();
	virtual void Update();
	
	Renderer render;
	Transform tf;
	BoxCollider bc;
	dfAnimator* animComp;
	dfParticleSystem* particleSys;
};

