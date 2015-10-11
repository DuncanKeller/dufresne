#pragma once
#include "gamesystem.h"
#include "Renderer.h"
#include "Transform.h"
#include "MatMath.h"
#include "glew.h"
#include <GL/GL.h>
#include "dfBasic.h"
#include "AssetManager.h"

class TestGameSystem :
	public GameSystem
{
public:
	TestGameSystem(void);
	virtual ~TestGameSystem(void);
	virtual void Init();
	virtual void Update();

	
	Renderer render;
	Transform tf;
};

