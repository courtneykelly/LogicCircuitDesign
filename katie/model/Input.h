#ifndef INPUT_H
#define INPUT_H

#include <iostream>   // for using cout
#include "Block.h"

using namespace std;


class Input : public Block
{
	public:
		Input(double,double,char,int);    // constructor
		~Input();   // deconstructor
		virtual int getValue();
		virtual void draw(SDL_Renderer*);
		virtual double getx();
		virtual double gety();
		virtual void setx(double);
		virtual void sety(double);
		virtual void setValue();

	private:
		double x;
		double y;
		char name;
		int value;
};


// constructor
Input::Input(double xPos, double yPos, char variable, int val) : Block()
{
	x = xPos;
	y = yPos;
	name = variable;
	value = val;
}


// deconstructor
Input::~Input()
{

}


int Input::getValue()
{
	return value;
}

void Input::draw(SDL_Renderer* renderer)
{
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
    else if( value == 1 ) {
    	SDL_RenderDrawLine( renderer, x + 15, y + 8, x + 15 , y + 22);
    }

}

double Input::getx()
{
	return x;
}
double Input::gety()
{	
	return y;
}
void Input::setx(double xNew)
{
	x = xNew;
}
void Input::sety(double yNew) 
{
	y = yNew;
}

void Input::setValue() {
	if(value == 1) {
		value = 0;
	}
	else {
		value = 1;
	}
}

#endif
