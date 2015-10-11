#include "RenderSystem.h"


RenderSystem::RenderSystem(void)
{
}


RenderSystem::~RenderSystem(void)
{
}


void RenderSystem::Init()
{
	
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
	int numberOfGroups = 20;
	int sizeOfAGroup = 100;

	// does not support negative depth values
	dfAssert(r.depth >= 0);

	if((int)renderBox.size() <= r.depth)
	{
		for(int i = 0; i < (r.depth+1) - (int)renderBox.size(); i++)
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

// todo better way than just passing around big vector
// needs to handle scene hirarchy eventually
void RenderSystem::RenderLoop(std::vector<GameSystem*>* gameSystems) 
{
	// todo move into broader scope
	int numberOfGroups = 20;
	int sizeOfAGroup = 100;

	for(int sIndex = 0; sIndex < gameSystems->size(); sIndex++)
	{
		// 1: add all render-able objects into render box
		for(int i = 0; i < renderBox.size(); i++)
		{
			renderBox[i].clear();
		}

		for(int i = 0; i < 5 /* number of components */; i++)
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