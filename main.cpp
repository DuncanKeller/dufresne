// TODO: Rename SDL-2.0.3 to just SDL
// TODO: Add SDL to additional include path
#include "SDL.h"
#include <stdlib.h>
#include <stdio.h>


void GameExit(int ReturnValue)
{
	exit( ReturnValue );
}

int main( int argc, char** argv )
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

	width = 640;
	height = 480;

	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL;

	SDL_Window *screen = SDL_CreateWindow("Dufresne",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width, height, flags);
	return 0;

}