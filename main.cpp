// TODO: Rename SDL-2.0.3 to just SDL
// TODO: Add SDL to additional include path

#define GLEW_STATIC

#include <windows.h>
#include "glew.h"
#include <GL/GL.h>
#include "SDL.h"
#include <stdlib.h>
#include <stdio.h>
#include "SDL_image.h"

#include "dfBasic.h"
#include "Input.h"
#include "TestGameSystem.h"
#include "RenderSystem.h"
#include "AssetManager.h"

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

	flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if(initted & flags != flags) 
	{
		printf("Failed to Init SDL Image\n");
		printf("IMG_Init: %s\n", IMG_GetError());
		GameExit( 1 );
		// handle error
	}

	// init gl
	SDL_GLContext glcontext;
    glcontext = SDL_GL_CreateContext(screen);
	GLint GlewInitResult = glewInit();
	if (GlewInitResult != GLEW_OK) 
	{
		printf("ERROR: %s\n",glewGetErrorString(GlewInitResult));
		GameExit( 1 );
	}
	glEnable(GL_TEXTURE_2D);
		
	assMan = AssetManager();
	std::wstring path = L"fart\\";
	assMan.CalculateLoosePackageSize(path);
	assMan.LoadLoosePackage(path);
	assMan.DebugTestWritePoolToFile();

	Input inp = Input();
	inp.Init();

	RenderSystem renderer = RenderSystem();
	renderer.Init();

	TestGameSystem test = TestGameSystem();
	test.Init();

	TestGameSystem test2 = TestGameSystem();
	test2.Init();
	test2.tf.SetScale(1.6f,1.6f,1);
	test2.render.renderInfo.depth = 2;

	TestGameSystem test3 = TestGameSystem();
	test3.Init();
	test3.tf.SetScale(-.2f,-.2f,1);
	test3.render.renderInfo.depth = 12;
	test3.tf.SetPos(0,.5,0);

	std::vector<GameSystem*> testRenderList;
	testRenderList.push_back(&test);
	testRenderList.push_back(&test2);
	testRenderList.push_back(&test3);
	
	while(true)
	{
		inp.Update();

		renderer.Update();

		renderer.RenderLoop(&testRenderList);

		SDL_GL_SwapWindow(screen);
	}


	return 0;

}
