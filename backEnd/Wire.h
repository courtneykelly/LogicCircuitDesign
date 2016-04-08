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
	Wire(Block*);	// constructor
	~Wire();   // deconstructor
	int getValue();

	void setPointer(Block* blockPtr);


    private:
	Block* blockPtr;
	int value;
};


// constructor
Wire::Wire(Block* ptr)
{
    blockPtr = ptr;
}


// destructor
Wire::~Wire()
{

}



int Wire::getValue()
{
    return (blockPtr->getValue());
}


void Wire::setPointer(Block* ptr)
{
    blockPtr = ptr;
}


#endif
