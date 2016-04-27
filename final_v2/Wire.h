#ifndef WIRE_H
#define WIRE_H

#include <iostream>   // for using cout
#include <cmath>
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
		void setForwardPtr(Block*);

		Block *getBackwardPtr();

		void movePoint1(int, int);
		void movePoint2(int, int);
		short *getPointXY(int);

		void draw(SDL_Renderer*);
		void deletePrep();
		int onWire();

	private:
		Block* forwardPtr; // points to the right to block input
		Block* backwardPtr; // points to the left to block ouput
		int value;

		// wire coordinates:
		int x1; // connected to block output
		int y1;
		int x2; // connected to block input
		int y2;
};


/* 	Constructor
*/
Wire::Wire(int x, int y)
{
	x1 = x;
	x2 = x;
	y1 = y;
	y2 = y;
}

/* 	Destructor
*/
Wire::~Wire()
{
}

/* 	Getter Function. Evaluate function with the value
	of the gate that the backward pointer of the wire
	points to.
*/
int Wire::getValue()
{
	return (backwardPtr->getValue());
}

/* 	Setter Function. Sets the pointer to the block passed
	to the function to the private data member backwardPtr.
*/
void Wire::setBackwardPtr(Block* ptr)
{
	backwardPtr = ptr;
}

/* 	Setter Function. Sets the pointer to the block passed
	to the function to the private data member forwardPtr.
*/
void Wire::setForwardPtr(Block* ptr)
{
	forwardPtr = ptr;
}

/* 	Move origin (first) point of the wire
*/
void Wire::movePoint1(int x, int y)
{
	x1 = x;
	y1 = y;
}

/*	Getter Function. Returns an array to the (x,y) coordingates
	of the endpoints of the wire. If a 1 is passed, then starting
	point of the wire is returned. If a 2 is passed, then the ending
	point of the wire is returned.
*/
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

/* 	Movement Function. Moves the pivot (second) point of the wire
*/
void Wire::movePoint2(int x, int y)
{
	x2 = x;
	y2 = y;
}

/* 	Draw Function. Draws a single wire
*/
void Wire::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

}

/*	Utility Function. Prepares to delete all the wires
	that are currently rendered to the screen.
*/
void Wire::deletePrep()
{
	if (forwardPtr != NULL && forwardPtr->getPortPtr(1) == this)
	{
		cout << "Setting reference within 'in1' to forward pointer to NULL" << endl;
		forwardPtr->setPortPtr(0, NULL);
	}

	if (forwardPtr != NULL && backwardPtr->getPortPtr(2) == this)
	{
		cout << "Setting reference to pointer within 'in0' to NULL" << endl;
		backwardPtr->setPortPtr(1, NULL);
	}
	else if (backwardPtr != NULL && backwardPtr->getPortPtr(0) == this)
	{
		cout << "Setting reference to pointer within 'out' to NULL" << endl;
		backwardPtr->setPortPtr(2, NULL);
	}
}

/*	Getter Function. Returns the value of the backward pointer, which is a pointer
	to the block where the wire originates from.
*/
Block * Wire::getBackwardPtr()
{
    return backwardPtr;
}


#endif
