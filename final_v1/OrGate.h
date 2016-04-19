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
		virtual void setValue();	// needed to change value of Inputs
		
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
OrGate::~OrGate()
{
}

double OrGate::getx()
{
	return x;
}

double OrGate::gety()
{
	return y;
}

void OrGate::setx(double newX)
{
	x = newX;
	updatePortXY();
}

void OrGate::sety(double newY)
{
	y = newY;
	updatePortXY();
}

int OrGate::getValue()
{
	int left;
	int right;
	if (getPortPtr(1) == NULL || getPortPtr(2) == NULL)
		return -1;
	left = getIn1()->getValue();
	right = getIn2()->getValue();
	if (left == -1 || right == -1)
		return -1;
	else
		return (left > 0 || right > 0);
}

void OrGate::draw(SDL_Renderer* renderer)
{
	// Change color to blue
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

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

	xPoints[91] = x;							// these points are for the rectangle
	yPoints[91] = y+staticGateHeight;			// attached to the semi circle
	xPoints[92] = x+(staticGateWidth);
	yPoints[92] = y+staticGateHeight;

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

	// lines, to represent ports
	boxRGBA(renderer, x+12, y, x-staticGateWidth/3, 
			y+2*staticLineLength, 255, 0, 50, 255);
	boxRGBA(renderer, x+12, y+staticGateHeight-2*staticLineLength, x-staticGateWidth/3, 
			y+staticGateHeight, 255, 0, 50, 255);
	boxRGBA(renderer, x + staticGateWidth + radius + (staticGateWidth/3), 
			y+(staticGateHeight/2)-(staticLineLength), x + staticGateWidth + radius,
			y+(staticGateHeight/2)+(staticLineLength),255, 0, 50, 255);

	// draw body of OR gate as a single polygon
	filledPolygonRGBA(renderer, xPoints, yPoints, numPoints, 255, 0, 50, 255);

	short* outPort = getPortXY(0);
	short* inPort1 = getPortXY(1);
	short* inPort2 = getPortXY(2);

	circleRGBA(renderer, outPort[0], outPort[1], 10, 0, 255, 0, 255);
	circleRGBA(renderer, inPort1[0], inPort1[1], 10, 0, 255, 0, 255);
	circleRGBA(renderer, inPort2[0], inPort2[1], 10, 0, 255, 0, 255);

	
}

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


void OrGate::updatePortXY()
{
	setInPort1(x-10, y);
	setInPort2(x-10, y+staticGateHeight);
	setOutPort(x+staticGateWidth+40, y + (staticGateHeight/2));
}

/* 	setValue function. Not needed in this class, but since virtual
	function, needs implementation.
*/
	void OrGate::setValue()
	{

	}

#endif
