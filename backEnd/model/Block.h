#ifndef BLOCK_H
#define BLOCK_H


#include <iostream>
#include <string>


using namespace std;

class Block {

	public:

		Block();	// constructor
		~Block();	// deconstructor

		virtual int getValue() = 0;      // print function	
		virtual void draw(SDL_Renderer*) = 0;
		virtual int onPort(int, int) = 0;

};


// base class pointer
Block::Block ()
{

}

Block::~Block ()
{

}


#endif
