#ifndef OUTPUT_H
#define	OUTPUT_H

#include <iostream>   // for using cout
#include "Block.h"

using namespace std;

class Output : public Block
{
	public:
		Output(double, double, char, int);    // constructor
		~Output();   // deconstructor
		virtual int getValue();
		virtual void draw(SDL_Renderer*);
		virtual double getx();
		virtual double gety();
		virtual void setx(double);
		virtual void sety(double);
		virtual Wire* getPortPtr(int);
		virtual void setPortPtr(int, Wire*);

		short *getPortXY(int port);
		virtual void setOutPort(short, short);
		virtual void setInPort1(short, short);
		virtual void setInPort2(short, short);

		virtual int onPort(int, int);
		virtual int onBlock(int, int);

		virtual void bringWires();

		virtual void setValue();

		virtual string getEquation();

		Wire* getWire1();

	private:
		double x;
		double y;
		char name;
		int value;

		Wire* in1; // pointer

		short inPort1[2]; // (x, y)
};


/* 	Constructor
*/
Output::Output(double xPos, double yPos, char variable, int val) : Block()
{
	x = xPos;			// 710
	y = yPos;			// 350
	name = variable;
	value = val;
	setInPort1(x-10, y+15);
	setPortPtr(1, NULL);
}


/* Deconstructor
*/
Output::~Output()
{
}

/*	Getter Function. Returns a pointer to the port of the 
	int specified. Integers 1 is the only valid option because
	the Output gate only has 1 input port. It returns a pointer
	to the wire connected to its input port. 
*/
Wire *Output::getPortPtr(int port)
{
	switch (port)
	{
		case 1:
			return in1; break;
		default:
			cout << "Invalid port call to getPortPtr. (only port=0)" << endl;
			return NULL;
	}
}	

/*	Setter Function. When a wire is connected to the input port 
	of an Output gate, a pointer to that wire is created and 
	passed to this function. It is then set to the in1 private
	data member.
*/
void Output::setPortPtr(int port, Wire* ptr)
{
	switch (port)
	{
		case 1:
			in1 = ptr; break;
		default:
			cout << "Invalid port call to setPortPtr. (only port=1 valid)" << endl;
	}
}

/*	Getter Function. Returns the value of the output port, but only
	when a wire is connected to it. It then calls the getValue function
	to get the evaluated value of the circuit, from that final wire 
	connected to it.
*/
int Output::getValue()
{
	if (getPortPtr(1) != NULL)
	{
		return (getPortPtr(1)->getValue());
	}
	else
	{
		return -1;
	}
}

/*	Virtual draw function. Draws the Input Gate according to the x and y values
	passed upon initialization. 
*/
void Output::draw(SDL_Renderer* renderer)
{
	
	// draw port in1
	short* outPort = getPortXY(1);
	circleRGBA(renderer, inPort1[0], inPort1[1], 10, 0, 255, 0, 255);

	boxRGBA( renderer, x-10, y+14, x, y+16, 0, 0, 0, 255);


	// Set Output Box Rectangles
	SDL_Rect outerBox;
	SDL_Rect zero;

	// Change color to blue
	SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

	outerBox.x = x;
	outerBox.y = y;
	outerBox.w = 30;
	outerBox.h = 30;

	zero.x = x+11;
	zero.y = y+8;
	zero.w = 9;
	zero.h = 14;

	SDL_RenderDrawRect( renderer, &outerBox );


	if (getValue() == 0) {
		SDL_RenderDrawRect( renderer, &zero );
	}
	else if (getValue() == 1) {
		SDL_RenderDrawLine( renderer, x+15, y+8, x+15, y+22 );
	}
		
}

/*	Getter Function. Returns the x coordinate of the Input Gate.
*/
double Output::getx()
{
	return x;
}

/*	Getter Function. Returns the y coordinate of the Input Gate.
*/
double Output::gety()
{
	return y;
}

/* 	Setter Function. Sets the x coordinate of the of the input 
	gate. This function has no functionality because the x value
	is set in the Constructor, but requires implementation 
	because it is a virtual function from the abstract base class
	Block
*/
void Output::setx(double)
{
}

/* 	Setter Function. Sets the y coordinate of the of the input 
	gate. This function has no functionality because the x value
	is set in the Constructor, but requires implementation 
	because it is a virtual function from the abstract base class
	Block
*/
void Output::sety(double) 
{

}

/*	Getter Function. Returns the array containing the x and y 
	coordinates of the port passed. This is the Output class, so 
	there is only an input port. 1 is the integer corresponding 
	to the input port, so if 0 is passed the coordinates of the
	input port are returned.
*/
short *Output::getPortXY(int port)
{
	if (port == 1)
		return inPort1;
	else
	{
		cout << "port " << port << " does not exist" << endl;
		return NULL;
	}
}

/*	Setter Function. This has no functionality because Output
	gates do not have any output ports. But since this is a 
	virtual function inherited from the base class Block, it
	requires implementation.
*/
void Output::setOutPort(short x, short y)
{
	cout << "Output does not have setOutPort implementation" << endl;
}

/*	Setter Function. Sets the coordinates of the input port
	to the coordinates passed into the function.
*/
void Output::setInPort1(short x, short y)
{
	inPort1[0] = x;
	inPort1[1] = y;

}

/* 	Setter Function. This has no functionality because there
	is only 1 input port for the Output block
*/
void Output::setInPort2(short x, short y)
{
	cout << "Input does not have setInPort1 implementation" << endl;
}

/*	Boolean Function. This function will return true if the x and 
	y coordinates passed to it (the x and y coordinates of the mouse)
	are on the output port of the input gate.
*/
int Output::onPort(int xMouse, int yMouse)
{
	// if on the 'out' port:
	if (sqrt(pow(xMouse - inPort1[0], 2) + pow(yMouse - inPort1[1], 2)) < 10)
		return 1; 
	else
		return -1;
}

/*	This Function has no functionality because you cannot change
	the value of the output port. That is set for you by our
	logic solver.
*/
int Output::onBlock(int xClick, int yClick)
{
	if (yClick >= y && yClick <= y+30) // in vertical bounds
	{
		if (xClick >= x && xClick <= x+30) // in horizontal bounds
		{
			cout << "on Output" << endl;
			return 1;
		}
	}
	return 0;
}

/*	Movement Function. When you move any of the gates with wires that
	are connected to the Output gates, you want the wires to stay 
	connected to the Output gate no matter there the other gate moves.
	This function does just that. It makes sure the a and y coordinates of the 
	wires coming out of its output port stay in place.
*/
void Output::bringWires()
{
	if (getPortPtr(1) != NULL) // if pointer is conected
	{
		// then move wire to match ports
		getPortPtr(1)->movePoint2(getPortXY(1)[0], getPortXY(1)[1]);
	}

}

/* 	setValue function. Not needed in this class, but since virtual
	function, needs implementation.
 */
void Output::setValue()
{
}

/*	Getter Function. Returns the pointer to the wire connected to
	the output port of the Output block.
*/
Wire* Output::getWire1()
{
    return in1;
}

/* Returns equation of completed logic circuit by
   traversing the circuit recursively
*/
string Output::getEquation()
{
    string equation;

    equation = "z = " + ( getWire1()->getBackwardPtr() )->getEquation();

    return equation;
}


#endif
