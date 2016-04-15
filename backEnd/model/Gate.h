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
		virtual int getValue() = 0;
		virtual void draw(SDL_Renderer*) = 0;
		virtual int onPort(int, int) = 0;
		void setIn1(Wire *);
		void setIn2(Wire *);
		Wire* getIn1();
		Wire* getIn2();

		void setPortPtr(int, Wire*);
		short *getPortXY(int);

		void setOutPort(short, short);
		void setInPort1(short, short);
		void setInPort2(short, short);




	private:
		Wire* out;
		Wire* in1;
		Wire* in2;                // first element in the list

		// positional elements:
		short outPort[2]; // {x, y}
		short inPort1[2];
		short inPort2[2];


};


void Gate::setIn1(Wire *pointer)
{
	in1 = pointer;
}


void Gate::setIn2(Wire *pointer)
{
	in2 = pointer;
}

Wire* Gate::getIn1()
{

	return in1;
}

Wire* Gate::getIn2()
{
	return in2;
}


void Gate::setPortPtr(int port, Wire* ptr)
{
	switch (port)
	{
		case 0:
			out = ptr; break;
		case 1:
			in1 = ptr; break;
		case 2:
			in2 = ptr; break;	
	}
}


short *Gate::getPortXY(int port)
{
	if (port == 0)
		return outPort;
	else if (port == 1)
		return inPort1;
	else if (port == 2)
		return inPort2;
	else
	{
		cout << "port " << port << " does not exist" << endl;
		return NULL;
	}
}




void Gate::setOutPort(short x, short y)
{
	outPort[0] = x;
	outPort[1] = y;
}

void Gate::setInPort1(short x, short y)
{
	inPort1[0] = x;
	inPort1[1] = y;
}

void Gate::setInPort2(short x, short y)
{
	inPort2[0] = x;
	inPort2[1] = y;
}




#endif
