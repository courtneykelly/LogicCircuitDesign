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
		Wire(int, int);		// constructor
		~Wire();   			// deconstructor
		int getValue();

		void setBackwardPtr(Block*);	// Each wire has a forward pointer and a backward pointer, which
		void setForwardPtr(Block*);		// point to the two blocks the wire is connected to
		
		Block *getBackwardPtr();		// returns the backward pointer

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


// Constructor
Wire::Wire(int x, int y)
{
	x1 = x;
	x2 = x;
	y1 = y;
	y2 = y;
}


// Destructor
Wire::~Wire()
{
}

/*	Getter Function. Returns the "value" of the wire, by evaluating
	the value of the gate of the backwardPtr
*/
int Wire::getValue()
{
	return (backwardPtr->getValue());
}

/* 	Seeter Function. Sets the backward pointer to the block passed in.
*/
void Wire::setBackwardPtr(Block* ptr)
{
	backwardPtr = ptr;
}

/* 	Seeter Function. Sets the forward pointer to the block passed in.
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

/*	Getter Function. Returns the an array containing 
	the x an y coordinates of each end of the wire. If 
	you pass in a 1, it will return the x and y coordinates 
	of the point connected to block output. If you pass in 
	a 2, it will return the x and y coordinates of the point 
	connected to block input.
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

/* 	Move the pivot (second) point of the wire
*/
void Wire::movePoint2(int x, int y)
{
	x2 = x;
	y2 = y;
}

/* 	Draw a single wire
*/
void Wire::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

}

/* 	Delete preparations. This functions prepares to delete everything
	from the vectors and window.
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
	
/*	This function is unused at the moment. We will potentially use this to
	delete wires. 
*/
int Wire::onWire()
{
	int length;
	length = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

	cout << "length: " << length << endl;

	return -1;
}

/*	Returns the backward pointer of the wire. This function is used to determine
	the equation of the final logic circuit.
*/
Block * Wire::getBackwardPtr()
{
    return backwardPtr;
}

#endif
