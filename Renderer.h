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

// todo separate atlas and sprite into different structs / components / classes?
struct SpriteInfo
{
	union
	{
		float arr[6];
		struct
		{
			vec2 atlasPos;
			vec2 spriteSize;
			vec2 textureSize; // have to duplicate to store as float... todo has to be a better approach...
		};
	};
	
	float atlasMargin; // space on the edges 
	float atlasSpacing; // space in between tiles
};

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
	std::vector<ShaderUniform> uniforms; 
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
	SpriteInfo spriteInfo;
	TextureInfo* textureInfo;

	void SetStandardUniforms();
	
	static void Renderer::PrintShaderLog(const unsigned int& index);
	static void Renderer::PrintProgramLog (const unsigned int& index);
	static void InitDefaultShader();
	
	void SetTexture(TextureInfo &t);

	void InitSprite(TextureInfo &t, int rows, int colums, int margin, int spacing);
	void SetAtlasLocation(int xIndex, int yIndex);
	void SetAtlasLocation(float xPos, float Ypos);

	// todo: not sure if there is a better way to do this? 
	//Auto assign rect to transform and re-assign if needed
	bool visible;
	bool atlased;
	Rect* renderRect;
	
	float testFloat;
	int testInt;

private:
	static bool defaultShaderAssigned;
	static unsigned int defaultShaderProgram;
	static unsigned int defaultAtlasShaderProgram;
	static unsigned int CompileShaderFromSrc(const char* shader, GLuint type);
	
};

// todo - idea for renderer
// first, renderer iterates through all components that have a renderer enabled
// as it goes through, it creates a dynamic array for each unique "depth" found, and stores the component reference
// (remember not to use some stl shit since this is the renderer we're talking about)
// each depth array is sorted by shaderProgram, so that componenets with the same shader program are drawn together
// iterate through each array and call Render on the Renderer component