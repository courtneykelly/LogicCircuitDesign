#ifndef INPUT_H
#define INPUT_H

#include <iostream>   // for using cout
#include "Block.h"

using namespace std;

class Input : public Block
{
	public:
		Input(int);    // constructor
		~Input();   // deconstructor
		virtual int getValue();
		virtual void draw(SDL_Renderer*);
		virtual Wire* getPortPtr(int);
		virtual void setPortPtr(int, Wire*);

		virtual int onPort(int, int);

	private:
		int value;

		Wire* out;	

		short outPort[2];
};


// constructor
Input::Input(int val)
{
	value = val;
}


// destructor
Input::~Input()
{

}


int Input::getValue()
{
	return value;
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



// virtual draw function
void Input::draw(SDL_Renderer* renderer)
{
	short* outPort = getPortXY(0);
	short* inPort1 = getPortXY(1);
	short* inPort2 = getPortXY(2);

	circleRGBA(renderer, outPort[0], outPort[1], 10, 0, 255, 0, 255);
	circleRGBA(renderer, inPort1[0], inPort1[1], 10, 0, 255, 0, 255);
	circleRGBA(renderer, inPort2[0], inPort2[1], 10, 0, 255, 0, 255);

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
