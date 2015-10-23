#include "Renderer.h"

bool Renderer::defaultShaderAssigned = false;
unsigned int Renderer::defaultShaderProgram = 0;

Renderer::Renderer(void)
{
	visible = true;

	renderInfo.depth = 0;
	renderInfo.glShaderProgram = 0;
	renderInfo.glTexture = 0;
	// todo clear me out VVV
	//renderInfo.mesh;

	// only do once, all renderers can use this default shader
	if(!defaultShaderAssigned)
	{
		InitDefaultShader();
		defaultShaderAssigned = true;
	}
	
	CreateDefaultMesh(&renderInfo.mesh);
	renderInfo.glShaderProgram = defaultShaderProgram;
	SetStandardUniforms();

}

Renderer::~Renderer(void)
{
	dfComponent::~dfComponent();
}

void Renderer::Init()
{
	// set default render rectangle
	renderRect = 0;
	Transform* tf = gameSystem->GetComponent<Transform>();
	if(tf)
	{
		renderRect = &tf->rectangle;
		for(int i = 0; i < renderInfo.uniforms.size(); i++)
		{
			if(dfStrCmp("rect", renderInfo.uniforms[i].name))
			{
				renderInfo.uniforms[i].valueRect = renderRect;
				break;
			}
		}
	}
}

void Renderer::Update()
{
}

void Renderer::SetTexture(TextureInfo t)
{
	renderInfo.glTexture = t.glTexture;
	RectSize(t.width, t.height, *renderRect);
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

	// create default shader program
	defaultShaderProgram = glCreateProgram();

	unsigned int vs = CompileShaderFromSrc("layout(location = 0) in vec3 vertex_position; layout(location = 2) in vec2 in_texture_coordinates; out vec2 texture_coordinates; uniform vec2 resolution; uniform vec4 rect; uniform sampler2D basic_texture; void main () { texture_coordinates = in_texture_coordinates; if(vertex_position.x < 0.0 && vertex_position.y < 0.0) { gl_Position.x = ((rect.x / resolution.x) * 2) - 1; gl_Position.y = ((rect.y / resolution.y) * 2) - 1; texture_coordinates.x = 0; texture_coordinates.y = 0; } else if(vertex_position.x > 0.0 && vertex_position.y < 0.0) { gl_Position.x = (((rect.x + rect.z) / resolution.x) * 2) - 1; gl_Position.y = ((rect.y / resolution.y) * 2) - 1; texture_coordinates.x = 1; texture_coordinates.y = 0; } else if(vertex_position.x < 0.0 && vertex_position.y > 0.0) { gl_Position.x = ((rect.x / resolution.x) * 2) - 1; gl_Position.y = (((rect.y + rect.w) / resolution.y) * 2) - 1; texture_coordinates.x = 0; texture_coordinates.y = 1; } else if(vertex_position.x > 0.0 && vertex_position.y > 0.0) { gl_Position.x = (((rect.x + rect.z) / resolution.x) * 2) - 1; gl_Position.y = (((rect.y + rect.w) / resolution.y) * 2) - 1; texture_coordinates.x = 1; texture_coordinates.y = 1; } gl_Position.y *= -1; gl_Position.z = 0.0; gl_Position.w = 1.0; }  ", GL_VERTEX_SHADER);
	unsigned int fs = CompileShaderFromSrc("in vec2 texture_coordinates;uniform sampler2D basic_texture;out vec4 frag_color;void main () {vec4 texel = texture2D (basic_texture, texture_coordinates);frag_color = texel;}", GL_FRAGMENT_SHADER);

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

}

void Renderer::SetStandardUniforms()
{
	// todo AddUniform function?

	ShaderUniform uniformOne;
	uniformOne.type = DF_point2D;
	uniformOne.name = "resolution";
	uniformOne.valueInt = &(ScreenResolution.arr[0]);
	renderInfo.uniforms.push_back(uniformOne);

	ShaderUniform uniformTwo;
	uniformTwo.type = DF_float;
	uniformTwo.name = "time";
	uniformTwo.valueFloat = &(dfTotalTime);
	renderInfo.uniforms.push_back(uniformTwo);

	// todo global random
	ShaderUniform uniformThree;
	uniformThree.type = DF_float;
	uniformThree.name = "rand";
	//uniformThree.valueInt = &(ScreenResolution.arr[0]);
	renderInfo.uniforms.push_back(uniformThree);

	ShaderUniform uniformFour;
	uniformFour.type = DF_rect;
	uniformFour.name = "rect";
	uniformFour.valueRect = 0; // todo have to assign this after init when we have a transform. Better way to do this?
	renderInfo.uniforms.push_back(uniformFour);

	// todo need a way to deal w/ multiple textures, no textures, etc
	ShaderUniform uniformFive;
	uniformFive.type = DF_sampler2D;
	uniformFive.name = "basic_texture";
	uniformFive.valueUInt =&renderInfo.glTexture;
	renderInfo.uniforms.push_back(uniformFive);
}