// TODO: Rename SDL-2.0.3 to just SDL
// TODO: Add SDL to additional include path

#define GLEW_STATIC

#include <windows.h>
#include "glew.h"
#include <GL/GL.h>
#include "SDL.h"
#include <stdlib.h>
#include <stdio.h>

#include "AssetManager.h"
#include "Input.h"

#include "Renderer.h"


std::vector<std::vector<RenderInfo>> renderBox;

void GameExit(int ReturnValue)
{
	exit( ReturnValue );
}

int CALLBACK WinMain(
	  _In_ HINSTANCE hInstance,
	  _In_ HINSTANCE hPrevInstance,
	  _In_ LPSTR     lpCmdLine,
	  _In_ int       nCmdShow)
{
	int width = 0;
	int height = 0;
	int flags = 0;
	
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "Video initialization failed: %s\n",
			 SDL_GetError( ) );
		GameExit( 1 );
	}

	if( SDL_Init( SDL_INIT_JOYSTICK ) < 0 )
	{
		printf( "Input initialization failed: %s\n",
			 SDL_GetError( ) );
		GameExit( 1 );
	}

	if( SDL_Init( SDL_INIT_GAMECONTROLLER ) < 0 )
	{
		printf( "Input initialization failed: %s\n",
			 SDL_GetError( ) );
		GameExit( 1 );
	}
	
	width = 640;
	height = 480;

	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	//flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL;
	flags =  SDL_WINDOW_OPENGL;

	SDL_Window *screen = SDL_CreateWindow("Dufresne",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width, height, flags);
		
	AssetManager am = AssetManager();
	std::wstring path = L"fart\\";
	am.CalculateLoosePackageSize(path);
	am.LoadLoosePackage(path);
	am.DebugTestWritePoolToFile();

	Input inp = Input();
	inp.Init();
	
	while(true)
	{
		inp.Update();
	}


	return 0;

}


void InitRenderBox()
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


void AddToRenderBox(RenderInfo r)
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

void SortRenderBox(int boxIndex)
{
	// todo implement
}

void RenderLoop()
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