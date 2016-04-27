#ifndef ORGATE_H
#define ORGATE_H

#include <iostream>   // for using cout
#include "Block.h"
#include "Input.h"
#include "Wire.h"

using namespace std;

class OrGate : public Gate
{
	public:
		OrGate(double, double);    // constructor
		~OrGate();   // deconstructor
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
		// for drawing:
		double x;
		double y;
		double staticGateWidth;
		double staticGateHeight;
		double staticLineLength;

		// helper functions:
		void updatePortXY();

};


// constructor
OrGate::OrGate(double xTopLeft, double yTopLeft) : Gate()
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

// destructor
OrGate::~OrGate()
{
}

/*	Getter Function. Returns the private data member x 
	so it can be accessed outside the class
 */
double OrGate::getx()
{
	return x;
}

/*	Getter Function. Returns the private data member y 
	so it can be accessed outside the class
 */
double OrGate::gety()
{
	return y;
}

/* 	Setter Function. Takes in the new x value and updates
	private data member x. This was the draw function will
	place the OR gate in the appropriate location. This function
	is useful when clicking and dragging the OR gate, you can 
	constantly update its position and ports.
 */
void OrGate::setx(double newX)
{
	x = newX;
	updatePortXY();
}

/*	Setter Function. Takes in the new y values and updates the 
	private data member y. Same use a description for gety()
	function.
 */
void OrGate::sety(double newY)
{
	y = newY;
	updatePortXY();
}

/*	Returns the value of the OR gate based on the values
	of it's two inputs. For an OR gate it will only 
	return false if both of the input values are 0.
 */
int OrGate::getValue()
{
	int left;
	int right;
	if (getPortPtr(1) == NULL || getPortPtr(2) == NULL)
		return -1;
	left = getPortPtr(1)->getValue();
	right = getPortPtr(2)->getValue();
	if (left == -1 || right == -1)
		return -1;
	else
		return (left > 0 || right > 0);
}

/*	Draw Function. This virtual function is very specific 
	to this OR gate class. It takes in the renderer and
	draws the gate all based on the x and y private data
	members, which are continually changing.
 */
void OrGate::draw(SDL_Renderer* renderer)
{

	// draw ports

	short* outPort = getPortXY(0);
	short* inPort1 = getPortXY(1);
	short* inPort2 = getPortXY(2);

	circleRGBA(renderer, outPort[0], outPort[1], 10, 0, 255, 0, 255);
	circleRGBA(renderer, inPort1[0], inPort1[1], 10, 0, 255, 0, 255);
	circleRGBA(renderer, inPort2[0], inPort2[1], 10, 0, 255, 0, 255);

    // Set Trigonometry Values for drawing Half Circle
	double step = 2;					// step size= 2 degrees
	int numPoints = int(180/step*2 + 4);	// number of points based on step size
	short xPoints[numPoints];			
	short yPoints[numPoints];

	double theta = 270*PI/180;					// start theta=270 degrees and convert to radians
	double xCenter = x;							// x value of center point for semi circle
	double yCenter = y + staticGateHeight/2;	// y value of center point for semi circle
	double radius = staticGateHeight/2;			// radius of semi circle

	xPoints[0] = x;
	yPoints[0] = y;	
	for (int i=1; i<=(180/step); i++) {				// loop through number of points
		xPoints[i] = xCenter + radius*cos(theta);	// get x value based on theta, xCenter, and radius
		yPoints[i] = yCenter + radius*sin(theta);	// get y value based on theta, yCenter, and radius
		theta += step*PI/180;						// increment theta by step size, convert to radians
	}
	
	xPoints[91] = x;
	yPoints[91] = y+staticGateHeight;
	xPoints[92] = x+30;							// these points are for the rectangle
	yPoints[92] = y+staticGateHeight;			// attached to the semi circle
	xPoints[93] = x+30;
	yPoints[93] = y;

/*
	theta = 270*PI/180;						// reset theta
	xCenter = x + staticGateWidth;			// reset xCenter
	yCenter = y + (staticGateHeight/2);		// reset yCenter
	radius = staticGateHeight/2;			// reset radius

	for (int i=(numPoints-2); i>(92); i--) {			// loop through number of points
		xPoints[i] = xCenter + radius*cos(theta);		// get x value based on theta, xCenter, and radius
		yPoints[i] = yCenter + radius*sin(theta);		// get y value based on theta, yCenter, and radius
		theta += step*PI/180;							// increment theta by step size, convert to radians
	}

	xPoints[numPoints-1] = x+(staticGateWidth);
	yPoints[numPoints-1] = y;
*/

	// lines, to represent ports
	boxRGBA(renderer, x+12, y, x-staticGateWidth/3, 
			y+2*staticLineLength, 0, 0, 0, 255);
	boxRGBA(renderer, x+12, y+staticGateHeight-2*staticLineLength, x-staticGateWidth/3, 
			y+staticGateHeight, 0, 0, 0, 255);
	boxRGBA(renderer, x + staticGateWidth + radius + (staticGateWidth/3), 
			y+(staticGateHeight/2)-(staticLineLength), x + staticGateWidth + radius,
			y+(staticGateHeight/2)+(staticLineLength), 0, 0, 0, 255);

	// draw body of OR gate as a single polygon
	filledPolygonRGBA(renderer, xPoints, yPoints, 94, 255, 0, 50, 255);

	// draw
	filledPieRGBA(renderer, x+30, y+staticGateHeight-1, staticGateHeight-1, 270, 330, 255, 0, 50, 255);	
	filledPieRGBA(renderer, x+30, y+1, staticGateHeight, 30, 90, 255, 0, 50, 255);	

	//boxRGBA(renderer, x, y, x+staticGateWidth-8, y+staticGateHeight, 0, 50, 0, 255);
}


/*	OnPort Function. This function uses the Pythagoreon Theorem
	to detect if the mouse in on a port of a particular gate.
	This is useful when drawing wires, so our program only
	draws them in appropriate places and then can "click into
	place" if you get close to the port.
 */
int OrGate::onPort(int xMouse, int yMouse)
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

/*	Boolean Function. This function returns true when the x and y values passed
	into the function (usually a mouse click coordinates) are within the bounds 
	of the OR gate. This allows for the clicking and dragging of all OR gates
	on the logic canvas.
*/
int OrGate::onBlock(int xClick, int yClick)
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
void OrGate::updatePortXY()
{
	setInPort1(x-18, y+1);
	setInPort2(x-18, y+staticGateHeight-1);
	setOutPort(x+staticGateWidth+45, y + (staticGateHeight/2));

}

/* 	setValue function. Not needed in this class, but since virtual
	function, needs implementation.
*/
void OrGate::setValue()
{

}

string OrGate::getEquation()
{
    string equation;
    
    equation = "(" + ( getWire1()->getBackwardPtr() )->getEquation() + "+" + ( getWire2()->getBackwardPtr() )->getEquation() + ")";

    return equation;
}

#endif
