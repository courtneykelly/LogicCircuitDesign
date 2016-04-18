#ifndef INPUT_H
#define INPUT_H

#include <iostream>   // for using cout
#include "Block.h"
#include "Wire.h"

using namespace std;

class Input : public Block
{
	public:
		Input(int);    // constructor
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

	private:
		int value;

		Wire* out; // pointer

		short outPort[2]; // (x, y)
};


// constructor
Input::Input(int val)
{
	value = val;
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
			return out; break;
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
			out = ptr; break;
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
	// draw port (temporary)
	short* outPort = getPortXY(0);
	circleRGBA(renderer, outPort[0], outPort[1], 10, 0, 0, 255, 255);
}

double Input::getx()
{

}
double Input::gety()
{

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


#endif
