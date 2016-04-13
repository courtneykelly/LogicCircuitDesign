#ifndef GATE_H
#define GATE_H

#include <iostream>   // for using cout
#include "Block.h"
#include "Input.h"
#include "Wire.h"

using namespace std;

class Gate : public Block

{
	public:
		virtual int getValue() = 0;
		virtual void draw() = 0;
		//virtual void moveBlock(int,int);
		void setIn0(Wire *);
		void setIn1(Wire *);
		Wire* getIn0();
		Wire* getIn1();

	private:
		Wire* in0;
		Wire* in1;                // first element in the list
		
		//gate coordinates
		int x;
		int y;
};


void Gate::setIn0(Wire *pointer)
{
	in0 = pointer;
}


void Gate::setIn1(Wire *pointer)
{
	in1 = pointer;
}

Wire* Gate::getIn0()
{

	return in0;
}

Wire* Gate::getIn1()
{
	return in1;
}

/*void Gate::moveBlock(int x2,int y2)
{

  x = x2;
  y = y2;

}*/



// ------------------------------------------------------------------------- //

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

  /*short xPoints[9] = {100, 100, 150, 165, 170, 175, 170, 165, 150};
  short yPoints[9] = {100, 160, 160, 150, 140, 130, 120, 110, 100};

  filledPolygonRGBA(renderer, xPoints, yPoints, 9, 255, 0, 50, 255);*/
	
}





#endif
