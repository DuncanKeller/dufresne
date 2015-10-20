#include "RenderSystem.h"


RenderSystem::RenderSystem(void)
{
}


RenderSystem::~RenderSystem(void)
{
}


void RenderSystem::Init()
{
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	
}

void RenderSystem::Update()
{

}

unsigned int RenderSystem::CompileShader(ShaderInfo shader)
{
	unsigned int shaderIndex = glCreateShader (shader.vertFragType);
	glShaderSource (shaderIndex, 1, (const GLchar** )&shader.shaderFile.contents, NULL);
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
	// todo move to a more global scope
	int numberOfGroups = 20;
	int sizeOfAGroup = 100;

	// does not support negative depth values
	dfAssert(r.depth >= 0);
	int currentSize = (int)renderBox.size();

	if((int)renderBox.size() <= r.depth)
	{
		for(int i = 0; i < (r.depth+1) - currentSize; i++)
		{
			std::vector<RenderInfo> newBox;
			newBox.reserve(sizeOfAGroup);
			renderBox.push_back(newBox);
		}
	}

	renderBox[r.depth].push_back(r);

}

void RenderSystem::SortRenderBox(int boxIndex)
{
	// todo implement
}

// todo better way than just passing around big vector
// needs to handle scene hirarchy eventually
void RenderSystem::RenderLoop(std::vector<GameSystem*>* gameSystems) 
{
	// todo move into broader scope
	int numberOfGroups = 20;
	int sizeOfAGroup = 100;

	//glEnable(GL_CULL_FACE);  
	//glCullFace(GL_BACK);  
	// set gl state
	glClear(GL_COLOR_BUFFER_BIT);

	for(int i = 0; i < renderBox.size(); i++)
	{
		renderBox[i].clear();
	}
	
	// 1: add all render-able objects into render box
	for(int sIndex = 0; sIndex < gameSystems->size(); sIndex++)
	{
		

		Renderer* renderer = (*gameSystems)[sIndex]->GetComponent<Renderer>();
		if(renderer)
		{
			AddToRenderBox(renderer->renderInfo);
			
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

	for(int i = 0; i < renderBox.size(); i++)
	{
		for(int n = 0; n < (int)renderBox[i].size(); n++)
		{
			unsigned int newShaderProg = renderBox[i][n].glShaderProgram;
			if(firstRender) // always set shader program for the first render
			{
				firstRender = false;
				glUseProgram(newShaderProg);
			}
			// update uniforms from list
			for(int uIndex = 0; uIndex < DF_MAX_UNIFORMS; uIndex++) 
			{
				// todo log warning if it can't find the matching uniform name
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
					case DF_mat4x4:
						glUniformMatrix4fv (uniformLoc, 1, GL_FALSE, renderBox[i][n].uniforms[uIndex].valueFloat);
						break;
					case DF_sampler2D:
						// todo: fart, I forget how to use thisss
						//glUniform1i (uniformLoc, renderBox[i][n].glTexture);
						glUniform1i (uniformLoc, 0);
						break;
					case DF_vec2:
						glUniform2f(uniformLoc, renderBox[i][n].uniforms[uIndex].valueFloat[0],
							renderBox[i][n].uniforms[uIndex].valueFloat[1]);
						break;
					case DF_vec3:
						glUniform3f(uniformLoc, renderBox[i][n].uniforms[uIndex].valueFloat[0],
							renderBox[i][n].uniforms[uIndex].valueFloat[1],
							renderBox[i][n].uniforms[uIndex].valueFloat[2]);
						break;
					case DF_vec4:
						glUniform4f(uniformLoc, renderBox[i][n].uniforms[uIndex].valueFloat[0],
							renderBox[i][n].uniforms[uIndex].valueFloat[1],
							renderBox[i][n].uniforms[uIndex].valueFloat[2],
							renderBox[i][n].uniforms[uIndex].valueFloat[3]);
						break;
					}
				}
			}


			unsigned int newTexture = renderBox[i][n].glTexture;
			glActiveTexture(GL_TEXTURE0 + 0); // todo + 0 is which texture is passed into the shader... manage this somehow...
			glBindTexture (GL_TEXTURE_2D, newTexture);

			glBindVertexArray (renderBox[i][n].mesh.vertexArrayObject);
			glDrawArrays (GL_TRIANGLES, 0, renderBox[i][n].mesh.numVerts);

		}
	}
	

	// end gl stuff
	//glFlush(); 
}