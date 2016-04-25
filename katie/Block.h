#ifndef BLOCK_H
#define BLOCK_H


#include <iostream>
#include <string>

class Wire;

using namespace std;

class Block {
	

	public:

		Block();	// constructor
		~Block();	// deconstructor

		virtual int getValue() = 0;      // print function	
		virtual void draw(SDL_Renderer*) = 0;
		virtual int onPort(int, int) = 0;
		virtual int onBlock(int, int) = 0;

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

		virtual void bringWires() = 0;
		virtual void setValue() = 0;	// needed to change value of Inputs
};

// constructor
Block::Block()
{

}

Block::~Block ()
{

}



#endif
