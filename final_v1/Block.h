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
		
		
		virtual double getx() = 0;
		virtual double gety() = 0;
		virtual void setx(double) = 0;
		virtual void sety(double) = 0;

};


// base class pointer
Block::Block ()
{

}

Block::~Block ()
{

}


#endif
