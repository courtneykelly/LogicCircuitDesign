#ifndef BLOCK_H
#define BLOCK_H


#include <iostream>
#include <string>

class Wire; // careful!!

using namespace std;

class Block {

	public:

		Block();	// constructor
		~Block();	// deconstructor

		virtual int getValue() = 0;      // print function	
		virtual void draw(SDL_Renderer*) = 0;
		virtual int onPort(int, int) = 0;
		virtual short *getPortXY(int) = 0;
		virtual void setPortPtr(int, Wire*) = 0;

		virtual void setOutPort(short, short) = 0;
		virtual void setInPort1(short, short) = 0;
		virtual void setInPort2(short, short) = 0;

};


// base class pointer
Block::Block ()
{

}

Block::~Block ()
{

}


#endif
