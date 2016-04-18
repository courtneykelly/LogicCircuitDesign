#ifndef BLOCK_H
#define BLOCK_H


#include <iostream>
#include <string>
//#include "Wire.h"

class Wire;

using namespace std;

class Block {

	public:

		Block();	// constructor
		~Block();	// deconstructor

		virtual int getValue() = 0;      // print function	
		virtual void draw(SDL_Renderer*) = 0;
		virtual int onPort(int, int) = 0;

		virtual Wire *getPortPtr(int) = 0;
		virtual void setPortPtr(int, Wire*) = 0;

		virtual double getx() = 0;
		virtual double gety() = 0;
		virtual void setx(double) = 0;
		virtual void sety(double) = 0;

		virtual short *getPortXY(int) = 0;
		virtual void setOutPort(short, short) = 0;
		virtual void setInPort1(short, short) = 0;
		virtual void setInPort2(short, short) = 0;

		void bringWires();
};

// constructor
Block::Block()
{

}

Block::~Block ()
{

}
/*
void Block::bringWires()
{
	if (getPortPtr(0) != NULL) // if pointer is conected
	{
		// then move wire to match ports
		getPortPtr(0)->movePoint1(getPortXY(0)[0], getPortXY(0)[1]);
	}
	for (int i = 1; i <=2; i++)
	{
		if (getPortPtr(i) != NULL)
		{
			getPortPtr(i)->movePoint2(getPortXY(i)[0], getPortXY(i)[1]);
		}
	}
}
*/

#endif
