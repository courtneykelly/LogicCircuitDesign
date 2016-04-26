// logicCircuitDesign

// cse20212, final project

// main.cpp

// test the SDL window

#include "Window.h"
#include "Block.h"
#include "Gate.h"
#include "Input.h"
#include "Wire.h"
#include <SDL.h>


int main()
{

	Window screen;		// Create an Object of class type Window called screen
	bool quit = false;	// quit boolean used to exit from display window/gui
	SDL_Event e;		// create an SDL event to recognize click events, etc.


	/*	Main action while loop, will only exit the loop if
		the user exits the window with a click event. Calls
		our virtual draw functions for the wires and blocks
		(and gates, or gates, not gates, etc.). Also continually
		draws and updates the window itself.	
	*/
	while (!quit)
	{

		screen.drawWires();
		screen.drawBlocks();	// AND, OR, and NOT Gates

		screen.draw(); // draws, delays, then clears

		while (SDL_PollEvent( &e ) != 0 )	// Handles the quit event 
		{
			quit = screen.eventHandler(e);
		}
	}

	return 0;
}
