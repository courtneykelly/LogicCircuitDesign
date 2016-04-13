// logicCircuitDesign

// cse20212, final project

// main.cpp

// test the SDL window

#include "Window.h"
#include <SDL.h>


int main()
{
<<<<<<< HEAD
    Window screen;

    bool quit = false;

    SDL_Event e;


    while (!quit)
    {
	// drawing functions go here!
	screen.drawAndGate();      


    
	screen.draw(); // draws, delays, then clears

	while (SDL_PollEvent( &e ) != 0 )
=======
	Window screen;
	bool quit = false;
	SDL_Event e;

	while (!quit)
>>>>>>> 185647a3d0c78632742aa71662a5c5ae9d5cdca7
	{
		// drawing functions go here!

		screen.drawWires();

		screen.draw(); // draws, delays, then clears

		while (SDL_PollEvent( &e ) != 0 )
		{
			quit = screen.eventHandler(e);
		}
	}

	return 0;
}
