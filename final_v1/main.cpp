// logicCircuitDesign

// cse20212, final project

// main.cpp

// test the SDL window

#include "Window.h"
#include "Block.h"
	#include "Gate.h"
		// AndGate
		// OrGate
	#include "Input.h"
#include "Wire.h"
#include <SDL.h>


int main()
{

	Window screen;		// Create an Object of class type Window called screen
	bool quit = false;	// quit boolean used to exit from display window/gui
	SDL_Event e;		// create an SDL event to recognize click events, etc.

	////////////////////////////////
    	// user changes the following 2:	
    	Input inputA(0);			
    	Input inputB(1);			
	////////////////////////////////

	/*AndGate and_gate;
	//Gate or_gate(1);
	Block* ptr = &and_gate;

	Wire from_A0(&inputA, 1, 1);
	//Wire from_A1(&inputA);
	Wire from_B0(&inputB, 1, 1);
	//Wire from_B1(&inputB);

	and_gate.setIn0(&from_A0);
	and_gate.setIn1(&from_B0);

	//or_gate.setIn0(&from_A1);
	//or_gate.setIn1(&from_B1);

	//Wire from_or(&or_gate);

	Wire from_and(&and_gate, 1, 1);

	// evaluate
	cout << "AND=" << from_and.getValue() << endl;
	//cout << "OR=" << from_or.getValue() << endl;*/

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

		while (SDL_PollEvent( &e ) != 0 )
		{
			quit = screen.eventHandler(e);
		}
	}

	return 0;
}
