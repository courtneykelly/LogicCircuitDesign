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
		OrGate(double,double);    // constructor
		~OrGate();   // deconstructor
		virtual int getValue();
		virtual void draw(SDL_Renderer*);
		
	private:
		// for drawing:
		double x;
		double y;
		double staticGateWidth;
		double staticGateHeight;
		double staticLineLength;

};


// constructor
OrGate::OrGate(double xCenter, double yCenter) : Gate()
{
	setIn0(NULL);
	setIn1(NULL);

	staticGateWidth=50;	
	staticGateHeight=60;
	staticLineLength=1;

	x = xCenter;
	y = yCenter;
}

// destructor
OrGate::~OrGate()
{
}


int OrGate::getValue()
{
	int left;
	int right;
	left = getIn0()->getValue();
	right = getIn1()->getValue();
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
	
}

#endif
