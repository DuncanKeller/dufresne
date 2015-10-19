#include "Renderer.h"

bool Renderer::defaultShaderAssigned = false;
unsigned int Renderer::defaultShaderProgram = 0;

Renderer::Renderer(void)
{
	renderInfo.depth = 0;
	renderInfo.glShaderProgram = 0;
	// todo clear me out VVV
	//renderInfo.mesh;
	for(int i = 0; i < DF_MAX_UNIFORMS; i++) 
	{
		renderInfo.uniforms[i].arrSize = 0;
		renderInfo.uniforms[i].name = 0;
		renderInfo.uniforms[i].type = DF_null;
		renderInfo.uniforms[i].valueInt = 0;
	}

	// only do once, all renderers can use this default shader
	if(!defaultShaderAssigned)
	{
		InitDefaultShader();
		defaultShaderAssigned = true;
	}
}


Renderer::~Renderer(void)
{
	dfComponent::~dfComponent();
}

void Renderer::Init()
{

}

void Renderer::Update()
{

}

void Renderer::Render()
{

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
		//PrintShaderLog(shaderIndex);
		dfAssert(false); // shader failed to compile
		return 0;
	}

	return shaderIndex;
}

void Renderer::InitDefaultShader()
{
	// create default shader program
	defaultShaderProgram = glCreateProgram();

	unsigned int vs = CompileShaderFromSrc("layout(location = 0) in vec3 vertex_position;layout(location = 1) in vec2 in_texture_coordinates;out vec2 texture_coordinates;uniform mat4 model;uniform sampler2D basic_texture;void main () {texture_coordinates = in_texture_coordinates;gl_Position = model * vec4 (vertex_position, 1.0);}", GL_VERTEX_SHADER);
	unsigned int fs = CompileShaderFromSrc("in vec2 texture_coordinates;uniform sampler2D basic_texture;out vec4 frag_color;void main () {vec4 texel = texture2D (basic_texture, texture_coordinates);frag_color = texel;}", GL_FRAGMENT_SHADER);

	//unsigned int fs = CompileShaderFromSrc("in vec2 texture_coordinates;uniform sampler2D basic_texture;out vec4 frag_color;void main () {frag_color = vec4(texture_coordinates.x,texture_coordinates.y,1-texture_coordinates.x,1);}", GL_FRAGMENT_SHADER);

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

void Renderer::SetDefaultRenderInfo()
{
	renderInfo.depth = 10;
	renderInfo.glTexture = 0;
	CreateDefaultMesh(&renderInfo.mesh);
	renderInfo.glShaderProgram = defaultShaderProgram;
	renderInfo.uniforms[0].type = DF_mat4x4;
	renderInfo.uniforms[0].name = "model";
	renderInfo.uniforms[0].valueFloat = &(renderInfo.matrix->m[0]);
	renderInfo.uniforms[1].type = DF_sampler2D;
	renderInfo.uniforms[1].name = "basic_texture";
	renderInfo.uniforms[1].valueUInt = &renderInfo.glTexture;

}
