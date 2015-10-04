#pragma once
#include "glew.h"
#include "dfcomponent.h"
#include "Mesh.h"
#include "dfBasic.h"
#include "STDUNC.h"
#include <vector>
#include <windows.h>
//#include <GL/glut.h>
#include <GL/GL.h>

const int DF_MAX_UNIFORMS = 8;

struct ShaderUniform
{
	dfBasicType type;
	char* name;
	int arrSize;
	union
	{
		int* valueInt;
		float* valueFloat;
		float* valueFloatArr[16];
	};
};

struct RenderInfo
{
	int depth;
	unsigned int glShaderProgram;
	unsigned int glTexture;
	Mesh mesh;
	ShaderUniform uniforms[DF_MAX_UNIFORMS]; // todo dynamic arr, maybe?
	// Shader info
	// Texture info
};

class Renderer :
	public dfComponent
{
public:
	Renderer(void);
	virtual ~Renderer(void);
	virtual void Init();
	virtual void Update();

	RenderInfo renderInfo;

	void Render();
};

// todo - idea for renderer
// first, renderer iterates through all components that have a renderer enabled
// as it goes through, it creates a dynamic array for each unique "depth" found, and stores the component reference
// (remember not to use some stl shit since this is the renderer we're talking about)
// each depth array is sorted by shaderProgram, so that componenets with the same shader program are drawn together
// iterate through each array and call Render on the Renderer component