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


#endif
