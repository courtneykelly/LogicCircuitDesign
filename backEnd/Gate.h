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
		Wire* in0;
		Wire* in1;                // first element in the list

		// helper functions
		int doMath(int, int);

};

// constructor
Gate::Gate(int op)
{
	operation = op;
	in0 = NULL;
	in1 = NULL;
}

// destructor
Gate::~Gate()
{

}


void Gate::setIn0(Wire *pointer)
{
	in0 = pointer;
}

void Gate::setIn1(Wire *pointer)
{
	in1 = pointer;
}

int Gate::getValue()
{
	int left;
	int right;
	left = in0->getValue();
	right = in1->getValue();

	return doMath(left, right);
}

int Gate::doMath(int left, int right)
{
	switch(operation)
	{
		case 0:
			return (left > 0 && right > 0);
		case 1:
			return (left > 0 || right > 0);
		default:
			return -1;
	}
}

#endif
