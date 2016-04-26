#ifndef OUTPUT_H
#define	OUTPUT_H

#include <iostream>   // for using cout
#include <string>
#include "Block.h"

using namespace std;

class Output : public Block
{
	public:
		Output(double, double, char, int);    // constructor
		~Output();   // deconstructor
		virtual int getValue();
		virtual void draw(SDL_Renderer*);
		virtual double getx();
		virtual double gety();
		virtual void setx(double);
		virtual void sety(double);
		virtual Wire* getPortPtr(int);
		virtual void setPortPtr(int, Wire*);

		short *getPortXY(int port);
		virtual void setOutPort(short, short);
		virtual void setInPort1(short, short);
		virtual void setInPort2(short, short);

		virtual int onPort(int, int);
		virtual int onBlock(int, int);

		virtual void bringWires();

		virtual void setValue();

		virtual string getEquation();

		Wire* getWire1();

	private:
		double x;
		double y;
		char name;
		int value;

		Wire* in1; // pointer

		short inPort1[2]; // (x, y)
};


// constructor
Output::Output(double xPos, double yPos, char variable, int val) : Block()
{
	x = xPos;			// 710
	y = yPos;			// 350
	name = variable;
	value = val;
	setInPort1(x-10, y+15);
	setPortPtr(1, NULL);
}


// deconstructor
Output::~Output()
{

}

Wire *Output::getPortPtr(int port)
{
	switch (port)
	{
		case 1:
			return in1; break;
		default:
			cout << "Invalid port call to getPortPtr. (only port=0)" << endl;
			return NULL;
	}
}	


void Output::setPortPtr(int port, Wire* ptr)
{
	switch (port)
	{
		case 1:
			in1 = ptr; break;
		default:
			cout << "Invalid port call to setPortPtr. (only port=1 valid)" << endl;
	}
}

int Output::getValue()
{
	if (getPortPtr(1) != NULL)
	{
		return (getPortPtr(1)->getValue());
	}
	else
	{
		return -1;
	}
}

void Output::draw(SDL_Renderer* renderer)
{
	// hello!
	// must first get the value by running getValue() before displaying the number
	

	// draw port in1
	short* outPort = getPortXY(1);
	circleRGBA(renderer, inPort1[0], inPort1[1], 10, 0, 0, 255, 255);

	boxRGBA( renderer, x-10, y+14, x, y+16, 0, 0, 0, 255);


	// Set Output Box Rectangles
	SDL_Rect outerBox;
	SDL_Rect zero;

	// Change color to blue
	SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

	outerBox.x = x;
	outerBox.y = y;
	outerBox.w = 30;
	outerBox.h = 30;

	zero.x = x+11;
	zero.y = y+8;
	zero.w = 9;
	zero.h = 14;

	SDL_RenderDrawRect( renderer, &outerBox );


	if (getValue() == 0) {
		SDL_RenderDrawRect( renderer, &zero );
	}
	else if (getValue() == 1) {
		SDL_RenderDrawLine( renderer, x+15, y+8, x+15, y+22 );
	}
	//else {
	//	cout << "Error Drawing static outputs, value not 0 or 1" << endl;
	//}
		
}

double Output::getx()
{
	return x;
}
double Output::gety()
{
	return y;
}
void Output::setx(double)
{

}
void Output::sety(double) 
{

}

short *Output::getPortXY(int port)
{
	if (port == 1)
		return inPort1;
	else
	{
		cout << "port " << port << " does not exist" << endl;
		return NULL;
	}
}


void Output::setOutPort(short x, short y)
{
	cout << "Output does not have setOutPort implementation" << endl;
}

void Output::setInPort1(short x, short y)
{
	inPort1[0] = x;
	inPort1[1] = y;

}

void Output::setInPort2(short x, short y)
{
	cout << "Input does not have setInPort1 implementation" << endl;
}



int Output::onPort(int xMouse, int yMouse)
{
	// if on the 'out' port:
	if (sqrt(pow(xMouse - inPort1[0], 2) + pow(yMouse - inPort1[1], 2)) < 10)
		return 1; 
	else
		return -1;
}

int Output::onBlock(int xClick, int yClick)
{
	if (yClick >= y && yClick <= y+30) // in vertical bounds
	{
		if (xClick >= x && xClick <= x+30) // in horizontal bounds
		{
			cout << "on Output" << endl;
			return 1;
		}
	}
	return 0;
}

void Output::bringWires()
{
	if (getPortPtr(1) != NULL) // if pointer is conected
	{
		// then move wire to match ports
		getPortPtr(1)->movePoint2(getPortXY(1)[0], getPortXY(1)[1]);
	}

}


void Output::setValue()
{
}

Wire* Output::getWire1()
{
    return in1;
}

string Output::getEquation()
{
    string equation;

    equation = ( getWire1()->getBackwardPtr() )->getEquation();

    return equation;
}

#endif
