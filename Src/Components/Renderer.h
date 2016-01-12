#pragma once
#include "../Libs/glew.h"
#include "../Libs/BuitInShaders.h"
#include "dfcomponent.h"
#include "../Core/Mesh.h"
#include "../Core/dfBasic.h"
#include "../Core/STDUNC.h"
#include <vector>
#include <windows.h>
#include <GL/GL.h>
#include "../Core/MatMath.h"
#include "SDL.h"

#include "../System/AssetManager.h"
#include "Transform.h"

struct dfPrimitive;

struct SpriteInfo
{
	union
	{
		float arr[6];
		struct
		{
			vec2 atlasPos;
			vec2 spriteSize;
		};
	};
	
	float atlasMargin; // space on the edges 
	float atlasSpacing; // space in between tiles
	int atlasRows;
	int atlasColums;
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

const int MAX_GL_SHADERS = 32;
struct RenderInfo
{
	bool active;

	int depth;
	unsigned int glShaderProgram;
	unsigned int glTextures[MAX_GL_SHADERS];
	int numTextures;
	Mesh mesh;
	std::vector<ShaderUniform> uniforms; 
	mat4* matrix;
	vec4 color;
	dfPrimitive* primitive;
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

	static void InitEmptyRenderInfo(RenderInfo *info);
	
	static void SetStandardUniforms(std::vector<ShaderUniform> &uniforms);
	static void SetSpecialUniforms(RenderInfo &renderInfo, SpriteInfo &spriteInfo, Renderer* entity);
	void AddUniform(ShaderUniform newUniform);
	void AddUniformInt(const char* name, int* value);
	void AddUniformFloat(const char* name, float* value);
	void AddUniformRect(const char* name, Rect* value);
	void AddUniformVec2(const char* name, vec2* value);

	static void Renderer::PrintShaderLog(const unsigned int& index);
	static void Renderer::PrintProgramLog (const unsigned int& index);
	static unsigned int CompileShaderFromSrc(const char* shader, GLuint type);
	static bool Renderer::CheckShaderCompile(unsigned int shader);
	static bool Renderer::CheckShaderLink(unsigned int shader);
	static void InitDefaultShader();

	
	void SetTexture(TextureInfo &t);

	void InitSprite(TextureInfo &t, int rows, int colums, int margin, int spacing);
	void SetAtlasLocation(int xIndex, int yIndex);
	void SetAtlasLocation(float xPos, float Ypos);
	void SetAtlasLocation(int index);

	bool visible;
	bool atlased;
	Rect* renderRect;

private:
	static bool defaultShaderAssigned;
	static unsigned int defaultShaderProgram;
	static unsigned int defaultAtlasShaderProgram;
	
};