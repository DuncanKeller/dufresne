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
#include "tinyjson.h"

#include "dfBasic.h"
#include "Input.h"
#include "TestGameSystem.h"
#include "RenderSystem.h"
#include "AssetManager.h"
#include "BoxCollider.h"
#include "TileMap.h"

point2D ScreenResolution;
float dfTotalTime; // todo fill me
float dfDeltaTime; // todo fill me

void GameExit(int ReturnValue)
{
	exit( ReturnValue );
}

// todo move me outta here! (CollisionSystem class? overkill?)
void DoCollision(std::vector<GameSystem*>* gameSystems)
{
	for(int ai = 0; ai < gameSystems->size(); ai++)
	{
		BoxCollider* colliderA = (*gameSystems)[ai]->GetComponent<BoxCollider>();
		if(colliderA)
		{
			for(int bi = 0; bi < gameSystems->size(); bi++)
			{
				BoxCollider* colliderB = (*gameSystems)[bi]->GetComponent<BoxCollider>();
				if(colliderB && colliderA != colliderB)
				{
					colliderA->BoxBoxCollision(*colliderA, *colliderB);
				}
			}
		}
	}
}

int CALLBACK WinMain(
	  _In_ HINSTANCE hInstance,
	  _In_ HINSTANCE hPrevInstance,
	  _In_ LPSTR     lpCmdLine,
	  _In_ int       nCmdShow)
{
	int flags = 0;

	dfDeltaTime = 43.f;

	ScreenResolution.x = 640.f;
	ScreenResolution.y = 480.f;
	
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
		ScreenResolution.x, ScreenResolution.y, flags);

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

	tinyjson_init();
		
	assMan = AssetManager();
	std::wstring path = L"fart\\";
	assMan.CalculateLoosePackageSize(path);
	assMan.LoadLoosePackage(path);
	assMan.DebugTestWritePoolToFile();

	input = Input();
	input.Init();

	RenderSystem renderer = RenderSystem();
	renderer.Init();

	TestGameSystem test = TestGameSystem();
	test.Init();
	RectSize(50, 50, &test.tf.rectangle);
	test.GetComponent<BoxCollider>()->stationary = false;
	test.render.renderInfo.depth = 50;


	TileMap tmap = TileMap();
	tmap.Init();


	std::vector<GameSystem*> testRenderList;
	testRenderList.push_back(&test);
	for(int i = 0; i < tmap.tiles.size(); i++)
	{
		testRenderList.push_back(tmap.tiles[i]);
	}
	
	
	while(true)
	{
		input.Update();

		renderer.Update();

		test.Update();

		DoCollision(&testRenderList);
		
		renderer.RenderLoop(&testRenderList);

		SDL_GL_SwapWindow(screen);
	}


	return 0;

}
