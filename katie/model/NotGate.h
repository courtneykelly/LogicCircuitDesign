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
NotGate::NotGate(double xCenter, double yCenter) : Gate()
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
NotGate::~NotGate()
{
}


int NotGate::getValue()
{
	
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
}

#endif