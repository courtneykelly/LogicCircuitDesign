#ifndef GATE_H
#define GATE_H

#include <iostream>   // for using cout
#include "Block.h"
    #include "Input.h"
    #include "Wire.h"

    using namespace std;


class AndGate : public Gate
{
	public:
		AndGate();    // constructor
		~AndGate();   // deconstructor
		virtual int getValue();
		virtual void draw();
		
	private:
		// for drawing:
		short xCoord[10];
		short yCoord[10];
		short numPts;
};


// constructor
AndGate::AndGate()
{
	setIn0(NULL);
	setIn1(NULL);

	numPts = 10;
}

// destructor
AndGate::~AndGate()
{
}


int AndGate::getValue()
{
	int left;
	int right;
	left = getIn0()->getValue();
	right = getIn1()->getValue();
	return (left > 0 && right > 0);
}

void AndGate::draw()
{
	
}

#endif
