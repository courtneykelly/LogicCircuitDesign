#ifndef INPUT_H
#define INPUT_H

#include <iostream>   // for using cout
#include <vector>
#include "Block.h"
#include "Wire.h"

using namespace std;

class Input : public Block
{
	public:
		Input(double, double, char, int);    // constructor
		~Input();   // deconstructor
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
		virtual void setValue();	// needed to change value of Inputs

	private:
		double x;
		double y;
		char name;
		int value;

		vector<Wire*> out; // pointer

		short outPort[2]; // (x, y)
};


// constructor
Input::Input(double xPos, double yPos, char variable, int val) : Block()
{
	x = xPos;
	y = yPos;
	name = variable;
	value = val;
	setOutPort(x+40, y+15); 
}


// deconstructor
Input::~Input()
{

}

Wire *Input::getPortPtr(int port)
{
	switch (port)
	{
		case 0:
			cout << "Error. out port is a vector of pointers, not a pointer" << endl;
			return NULL; break;
		default:
			cout << "Invalid port call to getPortPtr. (only port=0)" << endl;
			return NULL;
	}
}	


void Input::setPortPtr(int port, Wire* ptr)
{
	switch (port)
	{
		case 0:
			out.push_back(ptr); break;
		default:
			cout << "Invalid port call to setPortPtr. (only port=0)" << endl;
	}
}

int Input::getValue()
{
	return value;
}

void Input::draw(SDL_Renderer* renderer)
{
	// draw port
	short* outPort = getPortXY(0);
	circleRGBA(renderer, outPort[0], outPort[1], 10, 0, 255, 0, 255);
	boxRGBA( renderer, x+30, y+14, x+40, y+16, 0, 0, 0, 255);
	
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

	if (value == 0) {
		SDL_RenderDrawRect( renderer, &zero );
	}
	else if (value == 1) {
		SDL_RenderDrawLine( renderer, x+15, y+8, x+15, y+22 );
	}
	else {
		cout << "Error Drawing static inputs, value not 0 or 1" << endl;
	}
}

double Input::getx()
{
	return x;
}
double Input::gety()
{
	return y;
}
void Input::setx(double)
{

}
void Input::sety(double) 
{

}

short *Input::getPortXY(int port)
{
	if (port == 0)
		return outPort;
	else
	{
		cout << "port " << port << " does not exist" << endl;
		return NULL;
	}
}


void Input::setOutPort(short x, short y)
{
	outPort[0] = x;
	outPort[1] = y;
}

void Input::setInPort1(short x, short y)
{
	cout << "Input does not have setInPort1 implementation" << endl;
}

void Input::setInPort2(short x, short y)
{
	cout << "Input does not have setInPort1 implementation" << endl;
}



int Input::onPort(int xMouse, int yMouse)
{
	// if on the 'out' port:
	if (sqrt(pow(xMouse - outPort[0], 2) + pow(yMouse - outPort[1], 2)) < 10)
		return 0; 
	else
		return -1;
}

int Input::onBlock(int xClick, int yClick)
{
	if (yClick >= y && yClick <= y+30) // in vertical bounds
	{
		if (xClick >= x && xClick <= x+30) // in horizontal bounds
		{
			return 1;
		}
	}
	return 0;
}

void Input::bringWires()
{
	int i;
	for (i = 0; i < out.size(); i++)
	{
		out[i]->movePoint1(getPortXY(0)[0], getPortXY(0)[1]);
	}
	/*
	if (getPortPtr(0) != NULL) // if pointer is conected
	{
		// then move wire to match ports
		getPortPtr(0)->movePoint1(getPortXY(0)[0], getPortXY(0)[1]);
	}
	*/
}

/* 	setValue function. Not needed in this class, but since virtual
	function, needs implementation.
 */
void Input::setValue()
{
	if (value == 1) {
		value = 0;
	}
	else {
		value = 1;
	}
}


#endif
