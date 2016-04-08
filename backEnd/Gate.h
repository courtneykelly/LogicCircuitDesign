#ifndef GATE_H
#define GATE_H

#include <iostream>   // for using cout
#include "Block.h"
#include "Input.h"
#include "Wire.h"

using namespace std;

class Gate : public Block

{
    public:
	Gate(int);    // constructor
	~Gate();   // deconstructor
	virtual int getValue();
	void setIn0(Wire *);
	void setIn1(Wire *);


    private:
	int operation;
	string label; // text description of what the label does
	int positon();

	Wire* in0;
	Wire* in1;                // first element in the list

	// helper functions
	int doMath(int, int);

};

// constructor
Gate::Gate(int op)
{
    operation = op;
    label = "Not defined";
    in0 = NULL;
    in1 = NULL;
}

// destructor
Gate::~Gate()
{

}

// set first input
void Gate::setIn0(Wire *pointer)
{
    in0 = pointer;
}


// set second input
void Gate::setIn1(Wire *pointer)
{
    in1 = pointer;
}


// return output value
int Gate::getValue()
{
    int left; // an input (bottom if stacked)
    int right; // other input
    left = in0->getValue();
    right = in1->getValue();

    return doMath(left, right);
}

// execute operation
int Gate::doMath(int left, int right)
{
    switch(operation)
    {
	case 0:
	    label = "AND";
	    return (left > 0 && right > 0);
	case 1:
	    label = "OR";
	    return (left > 0 || right > 0);
	default:
	    label = "Operation not on list";
	    return -1;
    }
}

#endif
