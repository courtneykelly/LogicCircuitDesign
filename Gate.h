#ifndef GATE_H
#define GATE_H

#include <iostream>   // for using cout
#include <vector>
#include "Block.h"
#include "Input.h"
#include "Wire.h"

using namespace std;

class Gate : public Block

{
	public:
		// position of gate
		virtual double getx() = 0;
		virtual double gety() = 0;
		virtual void setx(double) = 0;
		virtual void sety(double) = 0;

		// pointer from ports
		virtual Wire *getPortPtr(int);
		virtual void setPortPtr(int, Wire*);

		// position of ports
		virtual short *getPortXY(int);
		virtual void setOutPort(short, short);
		virtual void setInPort1(short, short);
		virtual void setInPort2(short, short);
		
		// value of gate
		virtual int getValue() = 0;
		virtual void setValue() = 0;	// needed to change value of Inputs	

		// ptrs to Input wires
		Wire * getWire1();
		Wire * getWire2();
		
		virtual void draw(SDL_Renderer*) = 0;
		virtual int onPort(int, int) = 0;
		virtual int onBlock(int, int) = 0;
		virtual void bringWires();


	private:
		vector<Wire*> out;
		Wire* in1;
		Wire* in2;                // first element in the list

		// positional elements:
		short outPort[2]; // {x, y}
		short inPort1[2];
		short inPort2[2];

};

/*	Getter Function. Returns a pointer to the port of the 
	int specified. Integers 1 and 2 are the only valid options.
	They return pointers to the two input wires on that gate, 
	in1 and in2. 
*/
Wire *Gate::getPortPtr(int port)
{
	switch (port)
	{
		case 0:
			cout << "might be an error" << endl;
			if (out.size() == 0)
				return NULL;
			else
				return out[0]; break;
		case 1:
			return in1; break;
		case 2:
			return in2; break;	
		default:
			cout << "Invalid port call to getPortPtr within class Gate" << endl;
			return NULL;
	}
}	

/*	Setter Function. This function sets the in1, in2, and out private
	data members. When a wire is connected to an Input port on
	a gate, this function is called to set the in1 pointer to
	the wire that is connected to it.
*/
void Gate::setPortPtr(int port, Wire* ptr)
{
	switch (port)
	{
		case 0:
			out.push_back(ptr); break;
		case 1:
			in1 = ptr; break;
		case 2:
			in2 = ptr; break;
		default:
			cout << "Invalid port call to setPortPtr" << endl;
	}
}

/*	Getter Function. Returns an array with the x and y coordinates 
	of the port requested. If a 0 is passed, the coordinates of the
	out port are returned. If a 1 is passed, the coordinates of the 
	1st (top) in port are returned. If a 2 is passed, the coordinates
	of the 2nd (bottom) in port are returned.
*/
short *Gate::getPortXY(int port)
{
	if (port == 0)
		return outPort;
	else if (port == 1)
		return inPort1;
	else if (port == 2)
		return inPort2;
	else {
		cout << "port " << port << " does not exist" << endl;
		return NULL;
	}
}

/*	Setter Function. Sets the x and y coordinates of the output port
	to the values passed into the function.	
*/
void Gate::setOutPort(short x, short y)
{
	outPort[0] = x;
	outPort[1] = y;
}

/*	Setter Function. Sets the x and y coordinates of the 1st input
	port to the values passed into the function.	
*/
void Gate::setInPort1(short x, short y)
{
	inPort1[0] = x;
	inPort1[1] = y;
}

/*	Setter Function. Sets the x and y coordinates of the 2nd input 
	port to the values passed into the function.	
*/
void Gate::setInPort2(short x, short y)
{
	inPort2[0] = x;
	inPort2[1] = y;
}

/*	Movement Function. When you click and drag any of the gates on
	the logic canvas, you want the wires that are attached to it 
	follow the movement of that gate. This function makes sure that
	if any wires are attached to the output port, or input ports 
	they stay attached, no matter where the gate moves.
*/
void Gate::bringWires()
{
	int i;
	for (i = 0; i < out.size(); i++) {
		out[i]->movePoint1(getPortXY(0)[0], getPortXY(0)[1]);
	}

	for (i = 1; i <=2; i++) {
		if (getPortPtr(i) != NULL)
		{
			getPortPtr(i)->movePoint2(getPortXY(i)[0], getPortXY(i)[1]);
		}
	}
}

/*	Getter Function. Returns in1, a pointer to the wire connected
	to the first input port.
*/
Wire * Gate::getWire1()
{
    return in1;
}

/*	Getter Function. Returns in2, a pointer to the wire connected
	to the second input port.
*/
Wire * Gate::getWire2()
{
    return in2;
}


#endif
