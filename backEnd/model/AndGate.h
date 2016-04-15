#ifndef ANDGATE_H
#define ANDGATE_H

#include <iostream>   // for using cout
#include "Block.h"
    #include "Input.h"
    #include "Wire.h"
#include <cmath>

using namespace std;


class AndGate : public Gate
{
	public:
		AndGate();    // constructor
		~AndGate();   // deconstructor
		virtual int getValue();
		virtual void draw(SDL_Renderer*);
		int onPort(int, int);
		
	private:
		// for drawing:
		short xCoord[10];
		short yCoord[10];
		short numPts;

/*
		short outPort[2]; // {x, y}
		short inPort1[2];
		short inPort2[2];
*/
};


// constructor
AndGate::AndGate()
{
	setIn1(NULL);
	setIn2(NULL);

	numPts = 10;

	// to test onPort:
	setOutPort(100, 100);
	setInPort1(100, 200);
	setInPort2(200, 100);
}

// destructor
AndGate::~AndGate()
{
}


// virtual getValue function
int AndGate::getValue()
{
	int left;
	int right;
	left = getIn1()->getValue();
	right = getIn2()->getValue();
	return (left > 0 && right > 0);
}


// virtual draw function
void AndGate::draw(SDL_Renderer* renderer)
{
	short* outPort = getPortXY(0);
	short* inPort1 = getPortXY(1);
	short* inPort2 = getPortXY(2);

	circleRGBA(renderer, outPort[0], outPort[1], 10, 0, 255, 0, 255);
	circleRGBA(renderer, inPort1[0], inPort1[1], 10, 0, 255, 0, 255);
	circleRGBA(renderer, inPort2[0], inPort2[1], 10, 0, 255, 0, 255);

}


int AndGate::onPort(int xMouse, int yMouse)
{

	short* outPort = getPortXY(0);
	short* inPort1 = getPortXY(1);
	short* inPort2 = getPortXY(2);

	if      (sqrt(pow(xMouse - outPort[0], 2) + pow(yMouse - outPort[1], 2)) < 10)
		return 0;
	else if (sqrt(pow(xMouse - inPort1[0], 2) + pow(yMouse - inPort1[1], 2)) < 10)
		return 1;
	else if (sqrt(pow(xMouse - inPort2[0], 2) + pow(yMouse - inPort2[1], 2)) < 10)
		return 2;


	return -1;
}

#endif
