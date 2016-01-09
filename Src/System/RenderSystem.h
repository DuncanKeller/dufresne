#pragma once
#include "../Entity/GameSystem.h"
#include "../Components/dfComponent.h"
#include "../Components/Renderer.h"
#include <stdlib.h>
#include "AssetManager.h"
#include "SDL.h"
#include "dfScene.h"
#include "../Core/DFCman.h"
#include "../Components/dfParticleSystem.h"
#include "../Components/bmpTextEntity.h"
#include "../Libs/BuitInShaders.h"

enum dfPrimitiveType
{
	dfPrimNONE,
	dfPrimRectangle,
	dfPrimLine,
	dfPrimCircle,
	dfPrimMax
};

struct dfPrimitive
{
	dfPrimitiveType type;
	int layer;
	union
	{
		struct { Rect rect; };
		struct { dfLine line; };
		struct { Circle circle; };
	};
	RenderInfo rInfo;
};

class RenderSystem :
	public GameSystem
{
public:
	RenderSystem(void);
	virtual ~RenderSystem(void);
	virtual void Init();
	virtual void Update();
	
	void UpdateResolution(int w, int h);

	void InitRenderBox();
	void AddToRenderBox(RenderInfo);
	void SortRenderBox(int);
	void ApplyUniforms(ShaderUniform uniform, unsigned int shaderProgram );
	void RenderLoop(dfScene* scene);

	unsigned int CompileShader(ShaderInfo shader);

	std::vector<std::vector<RenderInfo>> renderBox;

	// for post process
	GLuint frameBuffer; 
	GLuint colorBufferTexture;
	Mesh screenRect;
	unsigned int postProcessShaderProgram;
	unsigned int postProcessVert;
	unsigned int postProcessFrag;
	std::vector<ShaderUniform> postProcessUnifroms;

	static SDL_Window* window;

	// for drawing primatives
	static const int MAX_DFPRIMITIVES = 256;
	void SetupPrimitives();
	static int currentNumPrimitives;
	static dfPrimitive primitives[MAX_DFPRIMITIVES];
	static unsigned int primitiveRectShaderProg;
	static unsigned int primitiveCircleShaderProg;
	static unsigned int primitiveLineShaderProg;
	static void DrawRect(Rect r, vec4 color, int layer);
	static void DrawLine(dfLine line, vec4 color, int layer);
	static void DrawCircle(Circle c, vec4 color, int layer);
};

