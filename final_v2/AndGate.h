#ifndef ANDGATE_H
#define ANDGATE_H

#include <iostream>   // for using cout
#include "Block.h"
#include "Input.h"
#include "Wire.h"

#define PI 3.14159265

using namespace std;


class AndGate : public Gate 		// Inherits from the class Gate
{
	public:
		AndGate(double,double);    			// constructor
		~AndGate();   						// deconstructor
		virtual double getx();				// returns the top left point of x value of the AND gate
		virtual double gety();				// returns the top left point of x value of the AND gate
		virtual void setx(double);			// changes the x value of the AND gate 
		virtual void sety(double);			// changes the y value of the AND gate
		virtual int getValue();				// return value of AND gate based on inputs
		virtual void draw(SDL_Renderer*);	// draws the AND gate based on x and y values
		virtual int onPort(int, int);		// returns 1 or 0 if mouse is on a "port"
		virtual int onBlock(int, int);
		virtual void setValue();			// needed to change value of Inputs

		virtual string getEquation(); 		// returns string of logical equation

	private:
		// for drawing:
		double x;
		double y;
		double staticGateWidth;		// these static values are to ensure that all the 
		double staticGateHeight;	// gates are the same sizes
		double staticLineLength;

		// for drawing:
		short xCoord[10];
		short yCoord[10];
		short numPts;

		void updatePortXY();


};


// Constructor
AndGate::AndGate(double xTopLeft, double yTopLeft) : Gate()
{
	//setPortPtr(0, NULL);
	setPortPtr(1, NULL);
	setPortPtr(2, NULL);

	numPts = 10;

	staticGateWidth=50;	
	staticGateHeight=60;
	staticLineLength=1;

	x = xTopLeft;
	y = yTopLeft;

	updatePortXY();

}

// Destructor
AndGate::~AndGate()
{
}

/*	Getter Function. Returns the private data member x 
	so it can be accessed outside the class
 */
double AndGate::getx()
{
	return x;
}

/*	Getter Function. Returns the private data member y 
	so it can be accessed outside the class
 */
double AndGate::gety()
{
	return y;
}

/* 	Setter Function. Takes in the new x value and updates
	private data member x. This was the draw function will
	place the AND gate in the appropriate location. This function
	is useful when clicking and dragging the AND gate, you can 
	constantly update its position and ports.
 */
void AndGate::setx(double newX)
{
	x = newX;
	updatePortXY();

}

/*	Setter Function. Takes in the new y values and updates the 
	private data member y. Same use a description for gety()
	function.
 */
void AndGate::sety(double newY)
{
	y = newY;
	updatePortXY();
}

/*	Returns the value of the AND gate based on the values
	of it's two inputs. For an AND gate It will only 
	return true if both inputs (left and right) are equal
	to 1.
 */
int AndGate::getValue()
{
	int left;
	int right;
	if (getPortPtr(1) == NULL || getPortPtr(2) == NULL)
	{
		return -1;
	}
	else
	{
		left = getPortPtr(1)->getValue();
		right = getPortPtr(2)->getValue();
		if (left == -1 || right == -1)
		{
			return -1;
		}
		else
		{
			return (left > 0 && right > 0);
		}
	}
}

/*	Draw Function. This virtual function is very specific 
	to this AND gate class. It takes in the renderer and
	draws the gate all based on the x and y private data
	members, which are continually changing.
 */
void AndGate::draw(SDL_Renderer* renderer)
{
	// Change color to blue
	SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

	// Set Trigonometry Values for drawing Half Circle
	double step = 2;					// step size= 2 degrees
	int numPoints = int(180/step + 3);	// number of points based on step size
	short xPoints[numPoints];			
	short yPoints[numPoints];

	double theta = 270*PI/180;					// start theta=270 degrees and convert to radians
	double xCenter = x + staticGateWidth;		// x value of center point for semi circle
	double yCenter = y + staticGateHeight/2;	// y value of center point for semi circle
	double radius = staticGateHeight/2;			// radius of semi circle

	for (int i=0; i<(180/step); i++) {				// loop through number of points
		xPoints[i] = xCenter + radius*cos(theta);	// get x value based on theta, xCenter, and radius
		yPoints[i] = yCenter + radius*sin(theta);	// get y value based on theta, yCenter, and radius
		theta += step*PI/180;						// increment theta by step size, convert to radians
	}

	xPoints[numPoints-3] = x+staticGateWidth;		// these points are for the rectangle
	yPoints[numPoints-3] = y+staticGateHeight;		// attached to the semi circle
	xPoints[numPoints-2] = x;
	yPoints[numPoints-2] = y+staticGateHeight;
	xPoints[numPoints-1] = x;
	yPoints[numPoints-1] = y;

	// lines, to represent ports
	boxRGBA(renderer, x, y+staticGateHeight/4-staticLineLength, x-staticGateWidth/3, 
			y+staticGateHeight/4+staticLineLength, 0, 0, 0, 255);
	boxRGBA(renderer, x, y+3*staticGateHeight/4-staticLineLength, x-staticGateWidth/3, 
			y+3*staticGateHeight/4+staticLineLength, 0, 0, 0, 255);
	boxRGBA(renderer, x+(staticGateWidth)+(staticGateHeight/2)+(staticGateWidth/3), 
			y+(staticGateHeight/2)-(staticLineLength), x+(staticGateWidth)+(staticGateHeight/2),
			y+(staticGateHeight/2)+(staticLineLength), 0, 0, 0, 255);

	// draw body of AND gate as a single polygon
	filledPolygonRGBA(renderer, xPoints, yPoints, numPoints, 255, 0, 50, 255);

	short* outPort = getPortXY(0);
	short* inPort1 = getPortXY(1);
	short* inPort2 = getPortXY(2);

	circleRGBA(renderer, outPort[0], outPort[1], 10, 0, 255, 0, 255);
	circleRGBA(renderer, inPort1[0], inPort1[1], 10, 0, 255, 0, 255);
	circleRGBA(renderer, inPort2[0], inPort2[1], 10, 0, 255, 0, 255);
}

/*	OnPort Function. This function uses the Pythagoreon Theorem
	to detect if the mouse in on a port of a particular gate.
	This is useful when drawing wires, so our program only
	draws them in appropriate places and then can "click into
	place" if you get close to the port.
 */
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

int AndGate::onBlock(int xClick, int yClick)
{
	if (yClick >= y && yClick <= y+staticGateHeight) // in vertical bounds
	{
		if (xClick >= x && xClick <= x+staticGateWidth) // in horizontal bounds
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

void AndGate::updatePortXY()
{
	setInPort1(x-18, y+15);
	setInPort2(x-18, y+staticGateHeight-15);
	setOutPort(x+staticGateWidth+45, y + (staticGateHeight/2));


}

/* 	setValue function. Not needed in this class, but since virtual
	function, needs implementation.
 */
void AndGate::setValue()
{

}

string AndGate::getEquation()
{
    string equation = "(" + ( getWire1()->getBackwardPtr() )->getEquation() + ( getWire2()->getBackwardPtr() )->getEquation() + ")";

    return equation;
}


#endif
