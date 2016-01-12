#pragma once
#include "../Components/Renderer.h"
#include "../Components/Transform.h"
#include "../Core/dfBasic.h"
#include "../System/AssetManager.h"
#include "../System/Input.h"
#include "../Components/BoxCollider.h"
#include "../Core/STDUNC.h"
#include "../Components/dfAnimator.h"
#include "../System/SoundSystem.h"

class stdEntity : public Entity
{
public:
	stdEntity(void);
	virtual ~stdEntity(void);

	virtual void Init();
	virtual void Update();
	
	Renderer render;
	Transform tf;
	BoxCollider bc;
	dfAnimator animComp;
};

