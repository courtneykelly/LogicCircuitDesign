#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>
#include "Block.h"

#include <cmath>
using namespace std;

class Output : public Gate
{
    public:
	Output();
	~Output();
	virtual int getValue();
	//virtual void draw(SDL_Renderer*);
	//int onPort(int, int);

    private:

}

// Constructor
Output::Output()
{   
    setIn0(NULL);
}

// getValue function
int Output::getValue()
{
    return getIn0()->getValue();
}


#endif
