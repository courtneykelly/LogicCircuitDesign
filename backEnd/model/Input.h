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
		virtual int onPort(int, int);

	private:
		int value;
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

void Input::draw(SDL_Renderer* renderer)
{

}

int Input::onPort(int xMouse, int yMouse)
{
	
	return -1;
}

#endif
