#include "Renderer.h"
#include "../Entity/Entity.h"

bool Renderer::defaultShaderAssigned = false;
unsigned int Renderer::defaultShaderProgram = 0;
unsigned int Renderer::defaultAtlasShaderProgram = 0;

Renderer::Renderer(void)
{
	visible = true;
	atlased = false;

	InitEmptyRenderInfo(&renderInfo);
	
	spriteInfo.atlasMargin = 0.f;
	spriteInfo.atlasSpacing = 0.f;
	spriteInfo.atlasPos = vec2(0.f,0.f);
	spriteInfo.spriteSize = vec2(0.f,0.f);

	// only do once, all renderers can use this default shader
	if(!defaultShaderAssigned)
	{
		InitDefaultShader();
		defaultShaderAssigned = true;
	}
	
	CreateDefaultMesh(&renderInfo.mesh);
	renderInfo.glShaderProgram = defaultShaderProgram;
	Renderer::SetStandardUniforms(renderInfo.uniforms);
}

Renderer::~Renderer(void)
{
	dfComponent::~dfComponent();
}

void Renderer::InitEmptyRenderInfo(RenderInfo *info)
{
	info->active = true;
	info->depth = 0;
	info->glShaderProgram = 0;
	info->color = vec4(1.f,1.f,1.f,1.f);
	info->primitive = 0;
	info->matrix = 0;
	for(int i = 0; i < MAX_GL_SHADERS; i++)
		info->glTextures[i] = 0;
	info->numTextures = 0;
}

void Renderer::Init()
{
	dfComponent::Init();

	// set default render rectangle
	renderRect = 0;
	Transform* tf = entity->GetComponent<Transform>();
	if(tf)
	{
		renderRect = &tf->rectangle;
		Renderer::SetSpecialUniforms(renderInfo, spriteInfo, this);
	}
	
}

void Renderer::Update()
{
	dfComponent::Update();
}

void Renderer::SetTexture(TextureInfo &t)
{
	renderInfo.glTextures[renderInfo.numTextures] = t.glTexture;
	renderInfo.numTextures++;
	textureInfo = &t;
	RectSize(t.width, t.height, renderRect);
}

void Renderer::InitSprite(TextureInfo &t, int rows, int colums, int margin, int spacing)
{
	atlased = true;
	renderInfo.glShaderProgram = defaultAtlasShaderProgram;
	textureInfo = &t;
	SetTexture(t);
	spriteInfo.atlasMargin = margin;
	spriteInfo.atlasSpacing = spacing;
	spriteInfo.atlasRows = rows;
	spriteInfo.atlasColums = colums;

	int nonMarginWidth = t.width - (((colums - 1) * spacing) + (2 * margin));
	float spriteWidth = nonMarginWidth / colums;
	int nonMarginHeight = t.height - (((rows - 1) * spacing) + (2 * margin));
	float spriteHeight = nonMarginHeight / rows;
	spriteInfo.spriteSize = vec2(spriteWidth / textureInfo->width, spriteHeight / textureInfo->height);
	
	RectSize((int)spriteWidth, (int)spriteHeight, renderRect);
}

void Renderer::SetAtlasLocation(int xIndex, int yIndex)
{
	spriteInfo.atlasPos = vec2(
		((spriteInfo.spriteSize.x * xIndex * textureInfo->width) + spriteInfo.atlasMargin + (spriteInfo.atlasSpacing * xIndex)) / textureInfo->width, 
		((spriteInfo.spriteSize.y * yIndex * textureInfo->height) + spriteInfo.atlasMargin + (spriteInfo.atlasSpacing * yIndex)) / textureInfo->height);
}

void Renderer::SetAtlasLocation(float xPos, float yPos)
{
	spriteInfo.atlasPos = vec2(xPos, yPos);
}

void Renderer::SetAtlasLocation(int index)
{
	int xIndex = index % spriteInfo.atlasColums;
	int yIndex = index / spriteInfo.atlasColums;
	SetAtlasLocation(xIndex, yIndex);
}

void Renderer::SetRenderRect(Rect* r)
{
	renderRect = r;

	for(int cIndex = 0; cIndex < renderInfo.uniforms.size(); cIndex++)
	{
		if(dfStrCmp("rect", renderInfo.uniforms[cIndex].name))
		{
			renderInfo.uniforms[cIndex].valueRect = renderRect;
			break;
		}
	}
}

Rect* Renderer::GetRenderRect()
{
	return renderRect;
}


void Renderer::PrintShaderLog(const unsigned int& index)
{
	int max_length = 2048;
	int actual_length = 0;
	char log[2048];
	glGetShaderInfoLog (index, max_length, &actual_length, log);
	SDL_Log ("shader info log for GL index %i:\n%s\n", index, log);
	
}

void Renderer::PrintProgramLog (const unsigned int& index) 
{
	int max_length = 2048;
	int actual_length = 0;
	char log[2048];
	glGetProgramInfoLog (index, max_length, &actual_length, log);
	SDL_Log ("program info log for GL index %i:\n%s", index, log);
}

unsigned int Renderer::CompileShaderFromSrc(const char* shader, GLuint type)
{
	unsigned int shaderIndex = glCreateShader (type);
	glShaderSource (shaderIndex, 1, &shader, NULL);
	glCompileShader (shaderIndex);
	int params = -1;
	glGetShaderiv (shaderIndex, GL_COMPILE_STATUS, &params);
	if (GL_TRUE != params) 
	{
		SDL_Log ( "ERROR: GL shader index %i did not compile\n", shaderIndex);
		PrintShaderLog(shaderIndex);
		dfAssert(false); // shader failed to compile
		return 0;
	}

	return shaderIndex;
}

bool Renderer::CheckShaderCompile(unsigned int shader)
{
	GLint compileSuccess = GL_FALSE;
	glGetShaderiv( shader, GL_COMPILE_STATUS, &compileSuccess );
    if( compileSuccess != GL_TRUE )
    {
        dfLog( "Failed to compile shader");
		Renderer::PrintShaderLog(shader);
        dfAssert(false); // failed to compile shader
		return false;
    }
	return true;
}

bool Renderer::CheckShaderLink(unsigned int shaderProg)
{
	GLint compileSuccess = GL_FALSE;
	glGetProgramiv( shaderProg, GL_LINK_STATUS, &compileSuccess );
    if( compileSuccess != GL_TRUE )
    {
        dfLog( "Failed to compile shader");
		Renderer::PrintProgramLog(shaderProg);
        dfAssert(false); // failed to compile shader
		return false;
    }
	return true;
}


void Renderer::InitDefaultShader()
{
	// create default shader programs
	defaultShaderProgram = glCreateProgram();

	unsigned int vs = CompileShaderFromSrc(defaultVert, GL_VERTEX_SHADER);
	unsigned int fs = CompileShaderFromSrc(defaultFrag, GL_FRAGMENT_SHADER);
	unsigned int atlasFs = CompileShaderFromSrc(defaultAtlassedFrag, GL_FRAGMENT_SHADER);

	Renderer::CheckShaderCompile(vs);
	Renderer::CheckShaderCompile(fs);
	Renderer::CheckShaderCompile(atlasFs);

	glAttachShader (defaultShaderProgram, vs);
	glAttachShader (defaultShaderProgram, fs);
	glLinkProgram (defaultShaderProgram);
  
	Renderer::CheckShaderLink(defaultShaderProgram);
	
	defaultAtlasShaderProgram = glCreateProgram();
	glAttachShader (defaultAtlasShaderProgram, vs);
	glAttachShader (defaultAtlasShaderProgram, atlasFs);
	glLinkProgram (defaultAtlasShaderProgram);
    
	Renderer::CheckShaderLink(defaultAtlasShaderProgram);
}

void Renderer::SetShader(const char* vert, const char* frag)
{
	unsigned int shaderProg = glCreateProgram();

	unsigned int vs = CompileShaderFromSrc(vert, GL_VERTEX_SHADER);
	unsigned int fs = CompileShaderFromSrc(frag, GL_FRAGMENT_SHADER);
	unsigned int atlasFs = CompileShaderFromSrc(defaultAtlassedFrag, GL_FRAGMENT_SHADER);

	Renderer::CheckShaderCompile(vs);
	Renderer::CheckShaderCompile(fs);
	Renderer::CheckShaderCompile(atlasFs);

	glAttachShader (shaderProg, vs);
	glAttachShader (shaderProg, fs);
	glLinkProgram (shaderProg);
  
	Renderer::CheckShaderLink(shaderProg);
	
	renderInfo.glShaderProgram = shaderProg;
}

void Renderer::AddUniform(ShaderUniform uniform)
{
	renderInfo.uniforms.push_back(uniform);
}

void Renderer::AddUniformInt(const char* name, int* value)
{
	ShaderUniform newUniform;
	newUniform.type = DF_int;
	newUniform.name = (char*)name;
	newUniform.valueInt = value;
	renderInfo.uniforms.push_back(newUniform);
}

void Renderer::AddUniformFloat(const char* name, float* value)
{
	ShaderUniform newUniform;
	newUniform.type = DF_float;
	newUniform.name = (char*)name;
	newUniform.valueFloat = value;
	renderInfo.uniforms.push_back(newUniform);
}

void Renderer::AddUniformRect(const char* name, Rect* value)
{
	ShaderUniform newUniform;
	newUniform.type = DF_rect;
	newUniform.name = (char*)name;
	newUniform.valueRect = value;
	renderInfo.uniforms.push_back(newUniform);
}

void Renderer::AddUniformVec2(const char* name, vec2* value)
{
	ShaderUniform newUniform;
	newUniform.type = DF_vec2;
	newUniform.name = (char*)name;
	newUniform.valueFloat = &value->x;
	renderInfo.uniforms.push_back(newUniform);
}


void Renderer::SetStandardUniforms(std::vector<ShaderUniform> &uniforms)
{
	ShaderUniform uniformOne;
	uniformOne.type = DF_point2D;
	uniformOne.name = "resolution";
	uniformOne.valueInt = &(GameResolution.arr[0]);
	uniforms.push_back(uniformOne);

	ShaderUniform uniformTwo;
	uniformTwo.type = DF_float;
	uniformTwo.name = "time";
	uniformTwo.valueFloat = &(dfTotalTime);
	uniforms.push_back(uniformTwo);

	ShaderUniform uniformThree;
	uniformThree.type = DF_float;
	uniformThree.name = "rand";
	uniformThree.valueFloat = &dfRandomFloat;
	uniforms.push_back(uniformThree);
}

void Renderer::SetSpecialUniforms(RenderInfo &renderInfo, SpriteInfo &spriteInfo, Renderer* entity)
{
	ShaderUniform uniformFour;
	uniformFour.type = DF_rect;
	uniformFour.name = "rect";
	uniformFour.valueRect = entity->renderRect;
	renderInfo.uniforms.push_back(uniformFour);

	ShaderUniform uniformFive;
	uniformFive.type = DF_sampler2D;
	uniformFive.name = "basic_texture";
	uniformFive.valueUInt = 0;
	renderInfo.uniforms.push_back(uniformFive);

	ShaderUniform uniformEight;
	uniformEight.type = DF_vec4;
	uniformEight.name = "inColor";
	uniformEight.valueFloat = &(renderInfo.color.x);
	renderInfo.uniforms.push_back(uniformEight);

	ShaderUniform uniformSix;
	uniformSix.type = DF_vec2;
	uniformSix.name = "atlasPos";
	uniformSix.valueFloat = &(spriteInfo.arr[0]);
	renderInfo.uniforms.push_back(uniformSix);

	ShaderUniform uniformSeven;
	uniformSeven.type = DF_vec2;
	uniformSeven.name = "spriteSize";
	uniformSeven.valueFloat = &(spriteInfo.arr[2]);
	renderInfo.uniforms.push_back(uniformSeven);

}