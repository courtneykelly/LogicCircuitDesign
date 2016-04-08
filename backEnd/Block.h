#ifndef BLOCK_H
#define BLOCK_H


#include <iostream>
#include <string>


using namespace std;

class Block {

    public:
	Block();	// constructor
	~Block();	// deconstructor
	virtual int getValue() = 0;          // print function


};


Block::Block ()
{

}

Block::~Block ()
{

}


#endif
