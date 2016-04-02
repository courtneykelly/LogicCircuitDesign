// Eric Krebs

// cse20212, lab8

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <stdio.h>
#include <cmath>

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

// functions:
bool init();
bool loadMedia();
void close();
SDL_Texture* loadTexture(std::string path);

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

SDL_Texture* gTexture = NULL;

bool init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
	success = false;
    }
    else
    {
	//Create Window
	gWindow = SDL_CreateWindow( "Just a square", SDL_WINDOWPOS_UNDEFINED, 
				    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
				    SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( gWindow == NULL )
	{
	    success = false;
	}
	else
	{
	    //Create renderer for window
	    gRenderer = SDL_CreateRenderer( gWindow, -1, 0 );
	    if( gRenderer == NULL )
	    {
		success = false;
	    }
	    else
	    {
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

		int imgFlags = IMG_INIT_PNG;
		if( !( IMG_Init( imgFlags ) & imgFlags ) )
		{
		    success = false;
		}
	    }
	}
    }
    return success;
}

bool loadMedia()
{
    bool success = true;

	gTexture = loadTexture( "and_gate.png" );
	if( gTexture == NULL )
	{
		printf( "Failed to load texture image!\n" );
		success = false;
	}

    return success;
}

void close()
{

    SDL_DestroyTexture( gTexture );
    gTexture = NULL;

    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface != NULL )
    {
	newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
	SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

int main( int argc, char* args[] )
{
    int x, y;

    //Start up SDL and create window
    if( init() )
    {
	//Load media
	if( loadMedia() )
	{	
	    bool quit = false;

	    SDL_Event e;

	    while( !quit )
	    {
		while( SDL_PollEvent( &e ) != 0 )
		{
		    if( e.type == SDL_QUIT )
		    {
			quit = true;
		    }

		}

		SDL_GetMouseState( &x, &y );

		//Clear screen
		SDL_RenderClear( gRenderer );

		//Render texture to screen
		gTexture.render(x, y, &gTexture);

		//Update screen
		SDL_RenderPresent( gRenderer );
	    }
	}
    }

    //Free resources and close SDL
    close();

    return 0;
}
