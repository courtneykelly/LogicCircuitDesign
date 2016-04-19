#ifndef NOTGATE_H
#define NOTGATE_H

#include <iostream>   // for using cout
#include "Block.h"
#include "Input.h"
#include "Wire.h"

#define PI 3.14159265

using namespace std;


class NotGate : public Gate
{
	public:
		NotGate(double,double);    // constructor
		~NotGate();   // deconstructor

		virtual double getx();
		virtual double gety();
		virtual void setx(double);
		virtual void sety(double);
		virtual int getValue();
		virtual void draw(SDL_Renderer*);
		virtual int onPort(int, int); // (xMouse, yMouse)
		virtual void setValue();	// needed to change value of Inputs

		
	private:
		int value;

		short outPort[2]; // (x, y)

		// for drawing:
		double x;
		double y;
		double staticGateWidth;
		double staticGateHeight;
		double staticLineLength;

		// helper function:
		void updatePortXY();
	
};


// constructor
NotGate::NotGate(double xTopLeft, double yTopLeft) : Gate()
{
	setPortPtr(0, NULL);
	setPortPtr(1, NULL);
	setPortPtr(2, NULL);

	staticGateWidth=50;	
	staticGateHeight=60;
	staticLineLength=1;

	x = xTopLeft;
	y = yTopLeft;

	updatePortXY();
}

// destructor
NotGate::~NotGate()
{
}


double NotGate::getx()
{
	return x;
}

double NotGate::gety()
{
	return y;
}

void NotGate::setx(double newX)
{
	x = newX;
	updatePortXY();
}

void NotGate::sety(double newY)
{
	y = newY;
	updatePortXY();
}

int NotGate::getValue()
{	
	int input;
	if (getPortPtr(1) == NULL)
		return -1;
	else // if input is defined
	{
		switch (getPortPtr(1)->getValue())
		{
			case -1: // undefined prior
				return -1; break;
			case 0: // invert it
				return 1; break;
			case 1: // invert it
				return 0; break;
			default: // error
				return -1; break;
		}
	}
}

void NotGate::draw(SDL_Renderer* renderer)
{
	// Change color to blue
	SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

	// draw lines
	boxRGBA( renderer, x, y+(staticGateHeight/2-staticLineLength), x-staticGateWidth/3, 
			y+(staticGateHeight/2)+staticLineLength, 255, 0, 50, 255 );
	boxRGBA( renderer, x+(2*staticGateWidth/3)+(staticGateWidth/3)-5, y+(staticGateHeight/2-staticLineLength), 
			x+(2*staticGateWidth/3)-10, y+(staticGateHeight/2)+staticLineLength, 255, 0, 50, 255 );
	// draw triangle
	filledTrigonRGBA( renderer, x, y+(staticGateHeight/4), x+(2*staticGateWidth/3), 
			y+(staticGateHeight/2), x, y+(3*staticGateHeight/4), 255, 0, 50, 255);


	// draw ports (temporary)
	short* outPort = getPortXY(0);
	short* inPort1 = getPortXY(1);

	circleRGBA(renderer, outPort[0], outPort[1], 10, 0, 255, 0, 255);
	circleRGBA(renderer, inPort1[0], inPort1[1], 10, 0, 255, 0, 255);

}

int NotGate::onPort(int xMouse, int yMouse)
{

	short* outPort = getPortXY(0);
	short* inPort1 = getPortXY(1);

	if      (sqrt(pow(xMouse - outPort[0], 2) + pow(yMouse - outPort[1], 2)) < 10)
		return 0;
	else if (sqrt(pow(xMouse - inPort1[0], 2) + pow(yMouse - inPort1[1], 2)) < 10)
		return 1;
	else
		return -1;
}

void NotGate::updatePortXY()
{
	setInPort1(x, y + (staticGateHeight/2));
	setOutPort(x+staticGateWidth, y + (staticGateHeight/2));
}

/* 	setValue function. Not needed in this class, but since virtual
	function, needs implementation.
*/
	void NotGate::setValue()
	{

	}


#endif
