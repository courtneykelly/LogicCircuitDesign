// logicCircuitDesign

// cse20212, final project

// main.cpp

// test the SDL window

#include "Window.h"
#include <SDL.h>


int main()
{
    Window screen;

    bool quit = false;

    SDL_Event e;

    while (!quit)
    {
	// drawing functions go here!




	screen.draw(); // draws, delays, then clears

	while (SDL_PollEvent( &e ) != 0 )
	{
	    switch(e.type)
	    {
		case SDL_QUIT:
		    quit = true;
		    break;
		case SDL_MOUSEBUTTONDOWN:
		    screen.drawLine();
		    break;
	    }
	}
    }

    return 0;
}
