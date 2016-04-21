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

		virtual double getx() = 0;
		virtual double gety() = 0;
		virtual void setx(double) = 0;
		virtual void sety(double) = 0;
		virtual void setValue() = 0;	// needed to change value of Inputs

		void setIn1(Wire *);
		void setIn2(Wire *);
		Wire* getIn1();
		Wire* getIn2();

		virtual Wire *getPortPtr(int);
		virtual void setPortPtr(int, Wire*);

		virtual short *getPortXY(int);
		virtual void setOutPort(short, short);
		virtual void setInPort1(short, short);
		virtual void setInPort2(short, short);
		
		virtual void bringWires();


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


// returns a pointer to the port of the int specified.
Wire *Gate::getPortPtr(int port)
{
	switch (port)
	{
		case 0:
			return out; break;
		case 1:
			return in1; break;
		case 2:
			return in2; break;	
		default:
			cout << "Invalid port call to getPortPtr within class Gate" << endl;
			return NULL;
	}
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
		default:
			cout << "Invalid port call to setPortPtr" << endl;
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




void Gate::bringWires()
{
	if (getPortPtr(0) != NULL) // if pointer is conected
	{
		// then move wire to match ports
		getPortPtr(0)->movePoint1(getPortXY(0)[0], getPortXY(0)[1]);
	}
	for (int i = 1; i <=2; i++)
	{
		if (getPortPtr(i) != NULL)
		{
			getPortPtr(i)->movePoint2(getPortXY(i)[0], getPortXY(i)[1]);
		}
	}
}







#endif
