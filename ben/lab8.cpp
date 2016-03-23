/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 295;
const int SCREEN_HEIGHT = 295;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia1();
bool loadMedia2();

//Frees media and shuts down SDL
void close1();
void close2();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
	
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gMedia1 = NULL;
SDL_Surface* gMedia2 = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}

bool loadMedia1()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gMedia1 = SDL_LoadBMP( "semrich.bmp" );
	if( gMedia1 == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "semrich.bmp", SDL_GetError() );
		success = false;
	}

	return success;
}

bool loadMedia2()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gMedia2 = SDL_LoadBMP( "semrich2.bmp" );
	if( gMedia2 == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "semrich2.bmp", SDL_GetError() );
		success = false;
	}

	return success;
}

void close1()
{
	//Deallocate surface
	SDL_FreeSurface( gMedia1 );
	gMedia1 = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

void close2()
{
	//Deallocate surface
	SDL_FreeSurface( gMedia2 );
	gMedia2 = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		if (!loadMedia1() | !loadMedia2() ) {
			printf( "Failed to load media!\n" );
		}
		else {			
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}

				//Apply the image1
				SDL_BlitSurface( gMedia1, NULL, gScreenSurface, NULL );
			
				//Update the surface
				SDL_UpdateWindowSurface( gWindow );

				//Delay
				SDL_Delay( 1000 );

				//Apply image2
				SDL_BlitSurface( gMedia2, NULL, gScreenSurface, NULL );

				//Update the surface
				SDL_UpdateWindowSurface( gWindow );

				//Delay
				SDL_Delay( 1000 );

			}		
		}
	}

	//Free resources and close SDL
	close1();
	close2();

	return 0;
}
