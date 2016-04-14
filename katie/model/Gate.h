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
		Gate();
		virtual int getValue() = 0;
		virtual void draw(SDL_Renderer*) = 0;
		void setIn0(Wire *);
		void setIn1(Wire *);
		Wire* getIn0();
		Wire* getIn1();

	private:
		Wire* in0;
		Wire* in1;                // first element in the list

};

Gate::Gate() : Block() 
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

Wire* Gate::getIn0()
{

	return in0;
}

Wire* Gate::getIn1()
{
	return in1;
}

#endif
