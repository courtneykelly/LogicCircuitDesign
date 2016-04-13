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
		virtual void draw();

	private:
		int value;
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


int Input::getValue()
{
	return value;
}

void Input::draw()
{

}

#endif
