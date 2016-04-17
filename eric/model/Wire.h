#ifndef WIRE_H
#define WIRE_H

#include <iostream>   // for using cout
#include "Block.h" // for pointers to objects
#include "Input.h"
#include "Gate.h"

using namespace std;

class Wire
{
	public:
		Wire(Block*, int, int);	// constructor
		~Wire();   // deconstructor
		int getValue();
		
		void setPointer(Block* blockPtr);
		void movePoint(int, int);
		void draw(SDL_Renderer*);
		

	private:
		Block* blockPtr;
		int value;

		// wire coordinates:
		int x1;
		int y1;
		int x2;
		int y2;
};


// constructor
Wire::Wire(Block* ptr, int x, int y)
{
	blockPtr = ptr;
	x1 = x;
	x2 = x;
	y1 = y;
	y2 = y;
	cout << "constructor x1: " << x1 << "  y1: " << y1 << endl;
}


// destructor
Wire::~Wire()
{

}


// evaluate function with:
int Wire::getValue()
{
	return (blockPtr->getValue());
}


// set the pointer to the block
void Wire::setPointer(Block* ptr)
{
	blockPtr = ptr;
}


// move the pivot (second) point of the wire
void Wire::movePoint(int x, int y)
{
	x2 = x;
	y2 = y;
}


// draw a single wire
void Wire::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	
}


#endif
