#pragma once
#include "Entity.h"
#include "dfComponent.h"
#include "Renderer.h"
#include <stdlib.h>
#include "AssetManager.h"
#include "SDL.h"
#include "dfScene.h"
#include "DFCman.h"

class RenderSystem :
	public Entity
{
public:
	RenderSystem(void);
	virtual ~RenderSystem(void);
	virtual void Init();
	virtual void Update();

	void InitRenderBox();
	void AddToRenderBox(RenderInfo);
	void SortRenderBox(int);
	void RenderLoop(dfScene* scene);

	unsigned int CompileShader(ShaderInfo shader);

	std::vector<std::vector<RenderInfo>> renderBox;


};

