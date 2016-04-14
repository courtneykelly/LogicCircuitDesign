#ifndef ANDGATE_H
#define ANDGATE_H

#include <iostream>   // for using cout
#include "Block.h"
#include "Input.h"
#include "Wire.h"

#define PI 3.14159265

using namespace std;


class AndGate : public Gate
{
	public:
		AndGate(double,double);    // constructor
		~AndGate();   // deconstructor
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
AndGate::AndGate(double xCenter, double yCenter) : Gate()
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
		y+staticGateHeight/4+staticLineLength, 255, 0, 50, 255);
	boxRGBA(renderer, x, y+3*staticGateHeight/4-staticLineLength, x-staticGateWidth/3, 
		y+3*staticGateHeight/4+staticLineLength, 255, 0, 50, 255);
	boxRGBA(renderer, x+(staticGateWidth)+(staticGateHeight/2)+(staticGateWidth/3), 
		y+(staticGateHeight/2)-(staticLineLength), x+(staticGateWidth)+(staticGateHeight/2),
		y+(staticGateHeight/2)+(staticLineLength),255, 0, 50, 255);

	// draw body of AND gate as a single polygon
	filledPolygonRGBA(renderer, xPoints, yPoints, numPoints, 255, 0, 50, 255);
}

#endif
