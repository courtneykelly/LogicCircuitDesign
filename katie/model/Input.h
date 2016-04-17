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

}

double Input::getx()
{

}
double Input::gety()
{

}
void Input::setx(double)
{

}
void Input::sety(double) 
{

}

#endif
