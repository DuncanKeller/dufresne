#include "Renderer.h"
#include "../Entity/Entity.h"

bool Renderer::defaultShaderAssigned = false;
unsigned int Renderer::defaultShaderProgram = 0;
unsigned int Renderer::defaultAtlasShaderProgram = 0;

Renderer::Renderer(void)
{
	visible = true;
	atlased = false;

	renderInfo.active = true;
	renderInfo.depth = 0;
	renderInfo.glShaderProgram = 0;
	renderInfo.glTexture = 0;
	renderInfo.color = vec4(1.f,1.f,1.f,1.f);
	renderInfo.primitive = 0;
	// todo clear me out VVV
	//renderInfo.mesh;
	
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
	renderInfo.glTexture = t.glTexture;
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

// todo move into more general scope
void Renderer::PrintShaderLog(const unsigned int& index)
{
	int max_length = 2048;
	int actual_length = 0;
	char log[2048];
	glGetShaderInfoLog (index, max_length, &actual_length, log);
	// todo dfLog
	SDL_Log ("shader info log for GL index %i:\n%s\n", index, log);
	
}
// todo move into more general scope
void Renderer::PrintProgramLog (const unsigned int& index) 
{
	int max_length = 2048;
	int actual_length = 0;
	char log[2048];
	glGetProgramInfoLog (index, max_length, &actual_length, log);
	// todo dfLog
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
		// todo logging
		//fprintf (stderr, "ERROR: GL shader index %i did not compile\n", shaderIndex);
		PrintShaderLog(shaderIndex);
		dfAssert(false); // shader failed to compile
		return 0;
	}

	return shaderIndex;
}

void Renderer::InitDefaultShader()
{
	// todo remove resolution from this and have it go through the same path as the AssetManager shaders
	// so that they get the default uniforms

	// create default shader programs
	defaultShaderProgram = glCreateProgram();

	unsigned int vs = CompileShaderFromSrc(defaultVert, GL_VERTEX_SHADER);
	
	unsigned int fs = CompileShaderFromSrc("#version 130\n#extension GL_ARB_explicit_attrib_location : require\n#extension GL_ARB_explicit_uniform_location : require\nin vec2 texture_coordinates;uniform sampler2D basic_texture;uniform vec2 atlasPos,spriteSize;uniform vec4 inColor;out vec4 frag_color;void main(){vec4 texel=texture2D(basic_texture,texture_coordinates);frag_color=vec4(texel.r*inColor.r,texel.g*inColor.g,texel.b*inColor.b,texel.a*inColor.a);if(frag_color.a==0||inColor.a==0)frag_color=vec4(0,0,0,0);}", GL_FRAGMENT_SHADER);
	
	unsigned int atlasFs = CompileShaderFromSrc(defaultAtlassedFrag, GL_FRAGMENT_SHADER);


	// todo duplication, find common place for this
	GLint compileSuccess = GL_FALSE;
	glGetShaderiv( vs, GL_COMPILE_STATUS, &compileSuccess );
    if( compileSuccess != GL_TRUE )
    {
        dfLog( "Failed to compile shader");
        //printShaderLog( vertexShader );
        dfAssert(false); // failed to compile shader
    }

	compileSuccess = GL_FALSE;
	glGetShaderiv( fs, GL_COMPILE_STATUS, &compileSuccess );
    if( compileSuccess != GL_TRUE )
    {
        dfLog( "Failed to compile shader");
        //printShaderLog( vertexShader );
        dfAssert(false); // failed to compile shader
    }

	compileSuccess = GL_FALSE;
	glGetShaderiv( atlasFs, GL_COMPILE_STATUS, &compileSuccess );
    if( compileSuccess != GL_TRUE )
    {
        dfLog( "Failed to compile shader");
        //printShaderLog( vertexShader );
        dfAssert(false); // failed to compile shader
    }


	glAttachShader (defaultShaderProgram, vs);
	glAttachShader (defaultShaderProgram, fs);
	glLinkProgram (defaultShaderProgram);

    compileSuccess = GL_TRUE;
    glGetProgramiv( defaultShaderProgram, GL_LINK_STATUS, &compileSuccess );
    if( compileSuccess != GL_TRUE )
    {
        dfLog( "Failed to link shader program");
        //printProgramLog( vertexShader );
        dfAssert(false); // failed to compile shader
    }

	
	defaultAtlasShaderProgram = glCreateProgram();
	glAttachShader (defaultAtlasShaderProgram, vs);
	glAttachShader (defaultAtlasShaderProgram, atlasFs);
	glLinkProgram (defaultAtlasShaderProgram);
    
	compileSuccess = GL_TRUE;
    glGetProgramiv( defaultAtlasShaderProgram, GL_LINK_STATUS, &compileSuccess );
    if( compileSuccess != GL_TRUE )
    {
        dfLog( "Failed to link shader program");
        //printProgramLog( vertexShader );
        dfAssert(false); // failed to compile shader
    }

}

void Renderer::SetStandardUniforms(std::vector<ShaderUniform> &uniforms)
{
	// todo AddUniform function?
	
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

	// todo need a way to deal w/ multiple textures, no textures, etc
	ShaderUniform uniformFive;
	uniformFive.type = DF_sampler2D;
	uniformFive.name = "basic_texture";
	uniformFive.valueUInt = &renderInfo.glTexture;
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