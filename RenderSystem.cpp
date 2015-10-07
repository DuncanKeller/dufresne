#include "RenderSystem.h"


RenderSystem::RenderSystem(void)
{
}


RenderSystem::~RenderSystem(void)
{
}


void RenderSystem::Init()
{
	// create default shader program
	defaultShaderProg = glCreateProgram();

	unsigned int vs = CompileShader("layout(location = 0) in vec3 vertex_position;layout(location = 2) in vec2 in_texture_coordinates;out vec2 texture_coordinates;uniform mat4 model;uniform sampler2D basic_texture;void main () {texture_coordinates = in_texture_coordinates;gl_Position = model * vec4 (vertex_position, 1.0);}", GL_VERTEX_SHADER);
	unsigned int fs = CompileShader("in vec2 texture_coordinates;uniform sampler2D basic_texture;out vec4 frag_color;void main () {vec4 texel = texture2D (basic_texture, texture_coordinates);frag_color = texel;}", GL_FRAGMENT_SHADER);

	glAttachShader (defaultShaderProg, vs);
	glAttachShader (defaultShaderProg, fs);
	glLinkProgram (defaultShaderProg);
}

void RenderSystem::Update()
{

}

unsigned int RenderSystem::CompileShader(const char* shader, GLuint type)
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
		return 0;
	}

	return shaderIndex;
}

void RenderSystem::InitRenderBox()
{
	int numberOfGroups = 20;
	int sizeOfAGroup = 100;

	renderBox.reserve(numberOfGroups);
	for(int i = 0; i < numberOfGroups; i++)
	{
		renderBox[i].reserve(100);
	}

	// gl operations
	glEnable (GL_BLEND);
	glDepthMask (GL_FALSE);
}


void RenderSystem::AddToRenderBox(RenderInfo r)
{
	int numberOfGroups = 20;
	int sizeOfAGroup = 100;

	// does not support negative depth values
	dfAssert(r.depth >= 0);

	if((int)renderBox.size() <= r.depth)
	{
		for(int i = 0; i < r.depth - (int)renderBox.size(); i++)
		{
			std::vector<RenderInfo> newBox;
			newBox.reserve(sizeOfAGroup);
			renderBox.push_back(newBox);
			if((i == r.depth - renderBox.size()) - 1)
			{
				renderBox[i].push_back(r);
			}
		}
	}
	else
	{
		renderBox[r.depth].push_back(r);
	}
}

void RenderSystem::SortRenderBox(int boxIndex)
{
	// todo implement
}

void RenderSystem::RenderLoop()
{
	int numberOfGroups = 20;
	int sizeOfAGroup = 100;

	// 1: add all render-able objects into render box
	for(int i = 0; i < numberOfGroups; i++)
	{
		renderBox[i].clear();
	}

	for(int i = 0; i < 5 /* number of components */; i++)
	{
		if(true) // component has renderer
		{
			//AddToRenderBox(thing);
		}
	}

	// 2: sort renderboxes by similar shader program
	for(int i = 0; i < numberOfGroups; i++)
	{
		SortRenderBox(i);
	}

	// 3 render all boxes
	unsigned int currentShaderProgram = 0;
	bool firstRender = true;

	for(int i = 0; i < numberOfGroups; i++)
	{
		for(int n = 0; n < (int)renderBox[i].size(); n++)
		{
			unsigned int newShaderProg = renderBox[i][n].glShaderProgram;
			if(firstRender) // always set shader program for the first render
			{
				firstRender = false;
				glUseProgram(newShaderProg);
				// update uniforms from list
				for(int uIndex = 0; uIndex < DF_MAX_UNIFORMS; uIndex++) 
				{
					if(renderBox[i][n].uniforms[uIndex].valueInt != 0) // todo is it OK just to check int, instead of depending on type?
					{
						int uniformLoc = glGetUniformLocation (newShaderProg, renderBox[i][n].uniforms[uIndex].name);
						// todo implement a buncha deez fuckers
						switch(renderBox[i][n].uniforms[uIndex].type)
						{
							case DF_int:
								glUniform1i (uniformLoc, *renderBox[i][n].uniforms[uIndex].valueInt);
								break;
							case DF_float:
								glUniform1f (uniformLoc, *renderBox[i][n].uniforms[uIndex].valueFloat);
								break;
							case DF_float_arr:
								dfAssert(renderBox[i][n].uniforms[uIndex].arrSize == 16);
								glUniformMatrix4fv (uniformLoc, 1, GL_FALSE, *renderBox[i][n].uniforms[uIndex].valueFloatArr);
								break;
						}
					}
				}

				unsigned int newTexture = renderBox[i][n].glTexture;
				glActiveTexture(GL_TEXTURE0 + 0); // todo + 0 is which texture is passed into the shader... manage this somehow...
				glBindTexture (GL_TEXTURE_2D, newTexture);

				glBindVertexArray (renderBox[i][n].mesh.vertextArrayObject);
				glDrawArrays (GL_TRIANGLES, 0, renderBox[i][n].mesh.numVerts);
			}
		}
	}
}