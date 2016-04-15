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
		Wire(int, int);	// constructor
		~Wire();   // deconstructor
		int getValue();

		void setBackwardPtr(Block*);
		void movePoint1(int, int);
		void movePoint2(int, int);
		short *getPointXY(int);
		void draw(SDL_Renderer*);
		void connect(Block*);	

	private:
		Block* forwardPtr; // connects to port 1
		Block* backwardPtr; // connects to port 0: used in computations
		int value;

		// wire coordinates:
		int x1;
		int y1;
		int x2;
		int y2;
};


// constructor
Wire::Wire(int x, int y)
{
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
	return (backwardPtr->getValue());
}


// set the pointer to the block
void Wire::setBackwardPtr(Block* ptr)
{
	backwardPtr = ptr;
}


// move origin (first) point of the wire
void Wire::movePoint1(int x, int y)
{
	x1 = x;
	y1 = y;
}


short *Wire::getPointXY(int point)
{
	if (point == 1)
	{
		short arr[2] = {x1, y1};
		return arr;
	}
	else if (point ==2)
	{
		short arr[2] = {x2, y2};
		return arr;
	}
	else
		return NULL;
}


// move the pivot (second) point of the wire
void Wire::movePoint2(int x, int y)
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


// connect the wire to the block
void Wire::connect(Block* ptr)
{
	
	
}


#endif
