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
		virtual int onBlock(int, int);
		virtual void setValue();	// needed to change value of Inputs

		virtual string getEquation();
		
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


/* 	Constructor
*/
NotGate::NotGate(double xTopLeft, double yTopLeft) : Gate()
{
	//setPortPtr(0, NULL);
	setPortPtr(1, NULL);
	setPortPtr(2, NULL);

	staticGateWidth=50;	
	staticGateHeight=60;
	staticLineLength=1;

	x = xTopLeft;
	y = yTopLeft;

	updatePortXY();
}

/* Deconstructor
*/
NotGate::~NotGate()
{
}

/*	Getter Function. Returns the private data member x 
	so it can be accessed outside the class
 */
double NotGate::getx()
{
	return x;
}

/*	Getter Function. Returns the private data member y 
	so it can be accessed outside the class
 */
double NotGate::gety()
{
	return y;
}

/* 	Setter Function. Takes in the new x value and updates
	private data member x. This was the draw function will
	place the NOT gate in the appropriate location. This function
	is useful when clicking and dragging the NOT gate, you can 
	constantly update its position and ports.
 */
void NotGate::setx(double newX)
{
	x = newX;
	updatePortXY();
}

/*	Setter Function. Takes in the new y values and updates the 
	private data member y. Same use a description for gety()
	function.
 */
void NotGate::sety(double newY)
{
	y = newY;
	updatePortXY();
}

/*	Returns the value of the NOT gate based on the values
	of it's one input. For an NOT gate it will simply change 
	the value to it's negation. (so from 0 to 1, or 1 to 0)
 */
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

/*	Draw Function. This virtual function is very specific 
	to this NOT gate class. It takes in the renderer and
	draws the gate all based on the x and y private data
	members, which are continually changing.
 */
void NotGate::draw(SDL_Renderer* renderer)
{
	// Change color to blue
	SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

	// draw lines
	boxRGBA( renderer, x, y+(staticGateHeight/2-staticLineLength), x-staticGateWidth/3, 
			y+(staticGateHeight/2)+staticLineLength, 0, 0, 0, 255 );
	boxRGBA( renderer, x+(2*staticGateWidth/3)+(staticGateWidth/3)-5, y+(staticGateHeight/2-staticLineLength), 
			x+(2*staticGateWidth/3)-10, y+(staticGateHeight/2)+staticLineLength, 0, 0, 0, 255 );
	// draw triangle
	filledTrigonRGBA( renderer, x, y+(staticGateHeight/4), x+(2*staticGateWidth/3), 
			y+(staticGateHeight/2), x, y+(3*staticGateHeight/4), 255, 0, 50, 255);	
	
	// draw ports
	short* outPort = getPortXY(0);
	short* inPort1 = getPortXY(1);

	circleRGBA(renderer, outPort[0], outPort[1], 10, 0, 255, 0, 255);
	circleRGBA(renderer, inPort1[0], inPort1[1], 10, 0, 255, 0, 255);

}

/*	OnPort Function. This function uses the Pythagoreon Theorem
	to detect if the mouse in on a port of a particular gate.
	This is useful when drawing wires, so our program only
	draws them in appropriate places and then can "click into
	place" if you get close to the port.
 */
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

/*	Boolean Function. This function returns true when the x and y values passed
	into the function (usually a mouse click coordinates) are within the bounds 
	of the NOT gate. This allows for the clicking and dragging of all NOT gates
	on the logic canvas.
*/
int NotGate::onBlock(int xClick, int yClick)
{

	if (yClick >= y+(staticGateHeight/4) && yClick <= y+(3*staticGateHeight/4)) // in vertical bounds
	{
		if (xClick >= x && xClick <= x+(2*staticGateWidth/3)) // in horizontal bounds
		{

			return 1;
		}
	}
	return 0;

}

/*	UpdatePort Function. This function updates the location 
	of the ports. This is called every time the value of 
	x and y is changed. 
*/
void NotGate::updatePortXY()
{

	setInPort1(x-10, y + (staticGateHeight/2));
	setOutPort(x+staticGateWidth, y + (staticGateHeight/2));

	setInPort1(x-18, y + (staticGateHeight/2));
	setOutPort(x+staticGateWidth-4, y + (staticGateHeight/2));

}

/* 	setValue function. Not needed in this class, but since virtual
	function, needs implementation.
 */
void NotGate::setValue()
{

}


/* Returns string of equation representing the output of
   this gate
*/
string NotGate::getEquation()
{
    string equation;
    
    equation = "(" + ( getWire1()->getBackwardPtr() )->getEquation() + ")'";

    return equation;
}


#endif
