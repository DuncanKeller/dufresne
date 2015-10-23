#pragma once
#include "glew.h"
#include "dfcomponent.h"
#include "Mesh.h"
#include "dfBasic.h"
#include "STDUNC.h"
#include <vector>
#include <windows.h>
#include <GL/GL.h>
#include "MatMath.h"
#include "SDL.h"

#include "AssetManager.h"
#include "Transform.h"

struct ShaderUniform
{
	dfBasicType type;
	char* name;
	int arrSize;
	union
	{
		unsigned int* valueUInt;
		int* valueInt;
		float* valueFloat;
		Rect* valueRect;
	};
};

struct RenderInfo
{
	int depth;
	unsigned int glShaderProgram;
	unsigned int glTexture;
	Mesh mesh;
	std::vector<ShaderUniform> uniforms; // todo dynamic arr, maybe?
	mat4* matrix;
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

	void SetStandardUniforms();
	
	static void Renderer::PrintShaderLog(const unsigned int& index);
	static void Renderer::PrintProgramLog (const unsigned int& index);
	static void InitDefaultShader();
	
	void SetTexture(TextureInfo t);

	// todo: not sure if there is a better way to do this? 
	//Auto assign rect to transform and re-assign if needed
	bool visible;
	Rect* renderRect;

private:
	static bool defaultShaderAssigned;
	static unsigned int defaultShaderProgram;
	static unsigned int CompileShaderFromSrc(const char* shader, GLuint type);
	
};

// todo - idea for renderer
// first, renderer iterates through all components that have a renderer enabled
// as it goes through, it creates a dynamic array for each unique "depth" found, and stores the component reference
// (remember not to use some stl shit since this is the renderer we're talking about)
// each depth array is sorted by shaderProgram, so that componenets with the same shader program are drawn together
// iterate through each array and call Render on the Renderer component