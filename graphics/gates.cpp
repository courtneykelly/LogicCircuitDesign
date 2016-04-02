// Loading AND gate onto the screen

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
	gWindow = SDL_CreateWindow( "LETSSSS GOOOOO", SDL_WINDOWPOS_UNDEFINED, 
				    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
				    SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( gWindow == NULL )
	{
	    success = false;
	}
	else
	{
	    //Create renderer for window
	    /*gRenderer = SDL_CreateRenderer( gWindow, -1, 0 );
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
	    }*/
		
	    //Initialize PNG loading
	    int imgFlags = IMG_INIT_PNG;
	    if( !( IMG_Init( imgFlags ) & imgFlags ) )
	    {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                success = false;
            }
            else
            {
           	//Get window surface
                gScreenSurface = SDL_GetWindowSurface( gWindow );
            }
	  }	
	}
    }
    return success;
}

bool loadMedia()
{
    bool success = true;

    return success;
}

void close()
{
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

SDL_Surface* loadSurface( std::string path )
{
	//The final optimized image
    SDL_Surface* optimizedSurface = NULL;

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

		    //Handle button events
		    //for( int i = 0; i < TOTAL_BUTTONS; ++i )
		    //{
		//	SDL
		  //  }

		}

		SDL_GetMouseState( &x, &y );

		//Clear screen
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );

		//Render red filled quad
		SDL_Rect fillRect = { x-40, y-25, 
				80, 50 };
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );	
		SDL_RenderFillRect( gRenderer, &fillRect );

		//Update screen
		SDL_RenderPresent( gRenderer );
	    }
	}
    }

    //Free resources and close SDL
    close();

    return 0;
}
