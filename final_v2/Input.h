#ifndef INPUT_H
#define INPUT_H

#include <iostream>   // for using cout
#include <vector>
#include "Block.h"
#include "Wire.h"

using namespace std;

class Input : public Block
{
	public:
		Input(double, double, char, int);    // constructor
		~Input();   // deconstructor
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
		virtual void setValue();	// needed to change value of Inputs

		virtual string getEquation();

	private:
		double x;
		double y;
		char name;
		int value;

		vector<Wire*> out; // pointer

		short outPort[2]; // (x, y)
};


/* 	Constructor
*/
Input::Input(double xPos, double yPos, char variable, int val) : Block()
{
	x = xPos;
	y = yPos;
	name = variable;
	value = val;
	setOutPort(x+40, y+15); 
}

/* 	Deconstructor
*/
Input::~Input()
{

}

/*	Getter Function. This function does not do anything in the Input class,
	but since it is a virtual function of the base class Block, it requires
	implementation. It should return a pointer to the wires connected to the
	input ports, but this is the Input.h class, and the input blocks do not
	have input ports, only output ports!
*/
Wire *Input::getPortPtr(int port)
{
	switch (port)
	{
		case 0:
			cout << "Error. out port is a vector of pointers, not a pointer" << endl;
			return NULL; break;
		default:
			cout << "Invalid port call to getPortPtr. (only port=0)" << endl;
			return NULL;
	}
}	

/*	Setter Function. For the Input class, when a wire is created front an Input
	out port, a pointer to that wire is created and passed to this function. 
	The pointer is then added to the out vector (a vector containing pointers to
	all wires stemming from the output port). Again since this is the Input class
	there are only output ports (case 0) and no input ports, hence only one case
	in the switch statement.
*/
void Input::setPortPtr(int port, Wire* ptr)
{
	switch (port)
	{
		case 0:
			out.push_back(ptr); break;
		default:
			cout << "Invalid port call to setPortPtr. (only port=0)" << endl;
	}
}

/*	Getter Function. Returns the value on the Input Gate (a, b, or c), which 
	is either 1 or 0 at any given time.
*/
int Input::getValue()
{
	return value;
}

/*	Virtual draw function. Draws the Input Gate according to the x and y values
	passed upon initialization. 
*/
void Input::draw(SDL_Renderer* renderer)
{
	// draw port
	short* outPort = getPortXY(0);
	circleRGBA(renderer, outPort[0], outPort[1], 10, 0, 255, 0, 255);
	boxRGBA( renderer, x+30, y+14, x+40, y+16, 0, 0, 0, 255);
	
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

	if (value == 0) {
		SDL_RenderDrawRect( renderer, &zero );
	}
	else if (value == 1) {
		SDL_RenderDrawLine( renderer, x+15, y+8, x+15, y+22 );
	}
	else {
		cout << "Error Drawing static inputs, value not 0 or 1" << endl;
	}
}

/*	Getter Function. Returns the x coordinate of the Input Gate.
*/
double Input::getx()
{
	return x;
}

/*	Getter Function. Returns the y coordinate of the Input Gate.
*/
double Input::gety()
{
	return y;
}

/* 	Setter Function. Sets the x coordinate of the of the input 
	gate. This function has no functionality because the x value
	is set in the Constructor, but requires implementation 
	because it is a virtual function from the abstract base class
	Block
*/
void Input::setx(double)
{
}

/* 	Setter Function. Sets the y coordinate of the of the input 
	gate. This function has no functionality because the x value
	is set in the Constructor, but requires implementation 
	because it is a virtual function from the abstract base class
	Block
*/
void Input::sety(double) 
{
}

/*	Getter Function. Returns the array containing the x and y 
	coordinates of the port passed. This is the Input class, so 
	there is only an output port. 0 is the integer corresponding 
	to the output port, so if 0 is passed the coordinates of the
	output port are returned.
*/
short *Input::getPortXY(int port)
{
	if (port == 0)
		return outPort;
	else
	{
		cout << "port " << port << " does not exist" << endl;
		return NULL;
	}
}

/*	Setter Function. Sets the coordinates of the output port
	to the coordinates passed into the function.
*/
void Input::setOutPort(short x, short y)
{
	outPort[0] = x;
	outPort[1] = y;
}

/*	Setter Function. This has no functionality because Input
	gates do not have any input ports. But since this is a 
	virtual function inherited from the base class Block, it
	requires implementation.
*/
void Input::setInPort1(short x, short y)
{
	cout << "Input does not have setInPort1 implementation" << endl;
}

/*	Setter Function. This has no functionality because Input
	gates do not have any input ports. But since this is a 
	virtual function inherited from the base class Block, it
	requires implementation.
*/
void Input::setInPort2(short x, short y)
{
	cout << "Input does not have setInPort1 implementation" << endl;
}

/*	Boolean Function. This function will return true if the x and 
	y coordinates passed to it (the x and y coordinates of the mouse)
	are on the output port of the input gate.
*/
int Input::onPort(int xMouse, int yMouse)
{
	// if on the 'out' port:
	if (sqrt(pow(xMouse - outPort[0], 2) + pow(yMouse - outPort[1], 2)) < 10)
		return 0; 
	else
		return -1;
}

/*	Boolean Function. This function will return true if the x and 
	y coordinates passed to it (the x and y coordinates of the mouse)
	are on the actual input gate. This function is necessary to change 
	the value of the input gate with a click.
*/
int Input::onBlock(int xClick, int yClick)
{
	if (yClick >= y && yClick <= y+30) // in vertical bounds
	{
		if (xClick >= x && xClick <= x+30) // in horizontal bounds
		{
			return 1;
		}
	}
	return 0;
}

/*	Movement Function. When you move any of the gates with wires that
	are connected to the Input gates, you want the wires to stay 
	connected to the Input gate no matter there the other gate moves.
	This function does just that. It makes sure the a and y coordinates of the 
	wires coming out of its output port stay in place.
*/
void Input::bringWires()
{
	int i;
	for (i = 0; i < out.size(); i++)
	{
		out[i]->movePoint1(getPortXY(0)[0], getPortXY(0)[1]);
	}
}

/* 	setValue function. Not needed in this class, but since virtual
	function, needs implementation.
 */
void Input::setValue()
{
	if (value == 1) {
		value = 0;
	}
	else {
		value = 1;
	}
}

/*	Getter Function. Returns the name of the Input Gate (either a, b, 
	or c). This function is used when constructing the equation of
	the logic circuit.
*/
string Input::getEquation()
{
    string equation(1, name);

    return equation;
}


#endif
