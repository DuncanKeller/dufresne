// TODO: Rename SDL-2.0.3 to just SDL
// TODO: Add SDL to additional include path

#define GLEW_STATIC

#include <windows.h>
#include "Libs/glew.h"
#include <GL/GL.h>
#include "SDL.h"
#include <stdlib.h>
#include <stdio.h>
#include "SDL_image.h"
#include "Libs/tinyjson.h"

#include "Core/dfBasic.h"
#include "System/Input.h"
#include "System/SceneManager.h"
#include "System\SoundSystem.h"
#include "Entity/TestGameSystem.h"
#include "System/RenderSystem.h"
#include "System/AssetManager.h"
#include "Components/BoxCollider.h"
#include "Entity/TileMap.h"
#include "Components/bmpTextEntity.h"
#include "..\SDL2_mixer-2.0.0\SDL_mixer.h"

// extern
point2D GameResolution;
point2D ScreenResolution;
float dfTotalTime; 
float dfDeltaTime; 
float dfRandomFloat;
std::map< std::type_index , dfComponent* > dfComponentMap;
std::map<char, int> asciiTable;

void GameExit(int ReturnValue)
{
	exit( ReturnValue );
}

TestEntity* testDude;
void SetupScene1()
{
	testDude = sceneMan.CreateSceneObject<TestEntity>();
	testDude->Init();
	//RectSize(50, 50, &test->tf.rectangle);
	testDude->GetComponent<BoxCollider>()->stationary = false;
	testDude->render.renderInfo.depth = 50;
	testDude->tf.SetPos(550.f, 200.f);
	testDude->bc.collisionRect = &testDude->tf.rectangle;
	testDude->bc.stationary = false;

	TileMap tmap = TileMap(L"fart\\tilemap1.json");
	tmap.Init();

	Entity* textEntity = sceneMan.CreateSceneObject<Entity>();
	Transform* tf = new Transform();
	tf->SetRect(20, 20, 1, 1);
	textEntity->RegisterComponent(tf);
	bmpTextEntity* bmpText = new bmpTextEntity(L"The first screen!", L"fart\\testFont.png", 16, 16);
	bmpText->layer = 31;
	textEntity->RegisterComponent(bmpText);
	bmpText->SetCharacterWidths(L"fart\\BFB Font Metrics.dat");
	bmpText->SetColor(vec4(0.8f, 0.f, 0.5f, 1.f));
	bmpText->SetSize(30);
}
void SetupScene2()
{
	testDude = sceneMan.CreateSceneObject<TestEntity>();
	testDude->Init();
	//RectSize(50, 50, &test->tf.rectangle);
	testDude->GetComponent<BoxCollider>()->stationary = false;
	testDude->render.renderInfo.depth = 50;
	testDude->tf.SetPos(50.f, 200.f);
	testDude->bc.collisionRect = &testDude->tf.rectangle;
	testDude->bc.stationary = false;

	Entity* textEntity = sceneMan.CreateSceneObject<Entity>();
	Transform* tf = new Transform();
	tf->SetRect(20, 20, 1, 1);
	textEntity->RegisterComponent(tf);
	bmpTextEntity* bmpText = new bmpTextEntity(L"The second screen!", L"fart\\testFont.png", 16, 16);
	bmpText->layer = 31;
	textEntity->RegisterComponent(bmpText);
	bmpText->SetCharacterWidths(L"fart\\BFB Font Metrics.dat");
	bmpText->SetColor(vec4(0.f, 0.6f, 0.2f, 1.f));
	bmpText->SetSize(30);

	TileMap tmap = TileMap(L"fart\\tilemap2.json");
	tmap.Init();
}

int CALLBACK WinMain(
	  _In_ HINSTANCE hInstance,
	  _In_ HINSTANCE hPrevInstance,
	  _In_ LPSTR     lpCmdLine,
	  _In_ int       nCmdShow)
{
	int flags = 0;

	dfDeltaTime = 43.f;
	
	ScreenResolution.x = 800.f;
	ScreenResolution.y = 600.f;
	
	GameResolution.x = 640.f;
	GameResolution.y = 480.f;
	
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

	if( SDL_Init( SDL_INIT_AUDIO ) < 0 )
	{
		printf( "Audio initialization failed: %s\n",
			 SDL_GetError( ) );
		GameExit( 1 );
	}

	//Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        GameExit( 1 );
    }

	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	//flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL;
	flags =  SDL_WINDOW_OPENGL;

	RenderSystem::window = SDL_CreateWindow("Dufresne",
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
    glcontext = SDL_GL_CreateContext(RenderSystem::window);
	GLint GlewInitResult = glewInit();
	if (GlewInitResult != GLEW_OK) 
	{
		printf("ERROR: %s\n",glewGetErrorString(GlewInitResult));
		GameExit( 1 );
	}
	glEnable(GL_TEXTURE_2D);

	tinyjson_init();

	InitEngine();
		
	assMan = AssetManager();
	std::wstring path = L"fart\\";
	assMan.CalculateLoosePackageSize(path);
	assMan.LoadLoosePackage(path);
	assMan.DebugTestWritePoolToFile();
	
	sfxMan = SoundSystem();
	sfxMan.Init();

	sceneMan.Init();

	input = Input();
	input.Init();
	
	dfScene* scene1 = sceneMan.CreateScene("scene-left");
	dfScene* scene2 = sceneMan.CreateScene("scene-right");
	scene1->setupFunc = &SetupScene1;
	scene2->setupFunc = &SetupScene2;
	
	sceneMan.LoadScene(scene1);

	Uint32 previousMiliseconds = 0;
	
	while(true)
	{
		Uint32 currentMiliseconds = SDL_GetTicks(); 
		dfRandomFloat = dfRand();
		dfTotalTime = currentMiliseconds / 1000.f;
		dfDeltaTime = (currentMiliseconds / 1000.f) - (previousMiliseconds / 1000.f);

		if(testDude->tf.rectangle.left > GameResolution.x)
		{
			sceneMan.LoadScene(scene2);
		}
		if(testDude->tf.rectangle.right < 0)
		{
			sceneMan.LoadScene(scene1);
		}

		if(input.keyboard.n1.tapped)
		{
			sceneMan.renderer.UpdateResolution(640, 480);
		}
		if(input.keyboard.n2.tapped)
		{
			sceneMan.renderer.UpdateResolution(300, 300);
		}
		if(input.keyboard.n3.tapped)
		{
			sceneMan.renderer.UpdateResolution(450, 300);
		}

		input.Update();

		sceneMan.Update();

		SDL_GL_SwapWindow(RenderSystem::window);
	}


	return 0;

}
