#pragma once
#include "gamesystem.h"
#include "Renderer.h"
#include <stdlib.h>

class RenderSystem :
	public GameSystem
{
public:
	RenderSystem(void);
	virtual ~RenderSystem(void);
	virtual void Init();
	virtual void Update();

	void InitRenderBox();
	void AddToRenderBox(RenderInfo);
	void SortRenderBox(int);
	void RenderLoop();

	unsigned int CompileShader(const char* shader, GLuint type);

	unsigned int defaultShaderProg;
	std::vector<std::vector<RenderInfo>> renderBox;
	

};

