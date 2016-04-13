#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

int main( int argc, char* args[] )
{
	if(!init())
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		bool quit = false;

		SDL_Event e;

		while( !quit )
		{
			while( SDL_PollEvent( &e ) != 0 )
			{
				if(e.type == SDL_QUIT )
				{
					quit = true;
				}

			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( gRenderer );

				
