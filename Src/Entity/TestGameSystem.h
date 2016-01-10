#pragma once
#include "Entity.h"
#include "../Components/Renderer.h"
#include "../Components/Transform.h"
#include "../Core/MatMath.h"
#include "../Libs/glew.h"
#include <GL/GL.h>
#include "../Core/dfBasic.h"
#include "../System/AssetManager.h"
#include "SDL_image.h"
#include "../System/Input.h"
#include "../Components/BoxCollider.h"
#include "../Core/STDUNC.h"
#include "../Components/dfAnimator.h"
#include "../Components/dfParticleSystem.h"
#include "../System/SoundSystem.h"

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

