// logicCircuitDesign

// Window.h

// contains all of the information for the window


#include <SDL.h>
#include "SDL2_gfxPrimitives.h"
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include "Block.h"
#include "Gate.h"
#include "Input.h"
#include "Wire.h"

#define PI 3.14159265

class Window {

	public:
		Window();
		~Window();

		int init();
		void draw();
		void drawAND(double, double);
		void drawOR(double, double);
		void drawNOT( double, double );
		int eventHandler(SDL_Event);

		void makeWire();
		void moveWire();
		//void moveBlocks();
		void drawBlocks();
		void drawWires();

	private:
		double screen_width;
		double screen_height;
		SDL_Window* window;
		SDL_Renderer* renderer;
		vector<Block*> blocks;
		vector<Wire*> wires;
		int action; // 0=none, 1=drawing wires, ...
		SDL_Rect viewController;
		SDL_Rect logicCanvas;
		SDL_Rect staticAND;
		SDL_Rect staticOR;
		SDL_Rect staticNOT;
		int borderSize;
		double staticGateWidth;
		double staticGateHeight;
		double staticLineLength; 
};


// constructor
Window::Window()
{
    screen_width = 1000;
    screen_height = 600;
    window = NULL;
    renderer = NULL;
	action = 0;
	borderSize=10;
	staticGateWidth=50;	
	staticGateHeight=60;
	staticLineLength=1;

	// Initialize View Controller
    viewController.x = screen_width - (screen_width/4);
    viewController.y = screen_height/2;
    viewController.w = screen_width/4 - borderSize;
    viewController.h = screen_height/2 - borderSize;

    // Initialize Logic Canvas
    logicCanvas.x = borderSize;
    logicCanvas.y = screen_height/3;
    logicCanvas.w = screen_width - (3*borderSize) - (viewController.w);
    logicCanvas.h = 2*screen_height/3 - borderSize;

    // Initlaize AND Gate in View Controller
    staticAND.x = viewController.x + (viewController.w / 2) - (staticGateWidth/2);
    staticAND.y = viewController.y + (viewController.h / 6) - (staticGateHeight/2);
    staticAND.w = staticGateWidth;
    staticAND.h = staticGateHeight;

    // Initialize OR Gate in View Controller
    staticOR.x = viewController.x + (viewController.w / 2) - (staticGateWidth/2);
    staticOR.y = viewController.y + (3*viewController.h / 6) - (staticGateHeight/2);
    staticOR.w = staticGateWidth;
    staticOR.h = staticGateHeight;

    // Initialize NOT Gate in View Controller
    staticNOT.x = viewController.x + (viewController.w / 2) - (staticGateWidth/2);
    staticNOT.y = viewController.y + (5*viewController.h / 6) - (staticGateHeight/2);
    staticNOT.w = staticGateWidth;
    staticNOT.h = staticGateHeight;

    init();
}


// destructor
Window::~Window()
{
    SDL_DestroyRenderer (renderer);
    SDL_DestroyWindow (window);
    window = NULL;
    renderer = NULL;

    SDL_Quit();
}


// initilaizes the window and renderer
int Window::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
		std::cout << "Could not initialize SDL: " << SDL_GetError() << std::endl;
		return -1;
    }

    // create window
    window = SDL_CreateWindow("Logic Circuit Design", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);

    // create renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
    {
		std::cout << "Could not create renderer: " << SDL_GetError() << std::endl;
		return -1;
    }

    // set renderer resolution
    SDL_RenderSetLogicalSize (renderer, screen_width, screen_height);

    // set Background color
    SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
    SDL_RenderClear (renderer);

    return 1;
}


void Window::draw()
{
	 // Change color to blue
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

    // Draw Static Gates
    
    //AND gate
    double x = viewController.x + (viewController.w / 2) - (staticGateWidth/2);
	double y = viewController.y + (viewController.h / 6) - (staticGateHeight/2);
	
	drawAND(x,y);

	//OR gate
	int x1 = viewController.x + (viewController.w / 2) - (staticGateWidth/2);
	int y1 = viewController.y + (3*viewController.h / 6) - (staticGateHeight/2);

	drawOR(x1, y1);

	//Not gate
	int x2 = viewController.x + (viewController.w / 2) - (staticGateWidth/2);
	int y2 = viewController.y + (5*viewController.h / 6) - (staticGateHeight/2);
	
	drawNOT(x2, y2);

    // Draw Rectangle for View Controller
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );     // Change Color to Black
    SDL_RenderDrawRect( renderer, &viewController );
    SDL_RenderDrawRect( renderer, &logicCanvas );


    SDL_RenderPresent(renderer); // draws it
    SDL_Delay(40); // 40 default
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer); // clear screen to white
}


// Conditionally call actions based on SDL event and variables
// NEEDS REDESIGN TO WORK FOR LOTS OF THINGS!
int Window::eventHandler(SDL_Event e)
{
	// cout << "e.type: " << e.type << endl;
	switch(e.type)
	{
		case SDL_QUIT:
			return 1; // quits
			break;
		case SDL_MOUSEBUTTONDOWN:

		  //get mouse position
		  int x,y,blockNum;
		  SDL_GetMouseState(&x, &y);

		  //check if mouse is inside a gate
		  /*for(int i = 0; i < blocks.size(); i++)
		    {
		      if( x < blocks[i].x && x > (blocks[i].x+ 100) && y < blocks[i].y &&  y > (blocks[i].y + 100)) {
				action=2;
				blockNum = i;
				break;
		      }
		    }*/
		    if(x>logicCanvas.x && x<(logicCanvas.x+logicCanvas.w) && y>logicCanvas.y && y<(logicCanvas.y+logicCanvas.h)) {
		    	makeWire();
		    	cout << "makeWire" << endl;
		    	break;
		    }
		    			
		case SDL_MOUSEBUTTONUP:
			action = 0;
			break;
	}
	
	switch (action)
	  {
	  case 1:
	    moveWire();
	    break;
	  /*case 2:
	    moveBlock(blockNum);
	    break;*/
	  default:
	    break;
	  }

	return 0; // continues
}


// Push back a new wire to vector wires
void Window::makeWire()
{
	int x;
	int y;
	SDL_GetMouseState(&x, &y);
	Wire* ptr = new Wire(NULL, x, y); // call constructor

	wires.push_back(ptr);
	action = 1;
}


void Window::moveWire()
{
	int x;
	int y;
	SDL_GetMouseState(&x, &y);
	wires.back()->movePoint(x, y);
}

/*void Window::moveBlock(int i)
{
  int x;
  int y;
  SDL_GetMouseState(&x,&y);
  blocks[i]->moveBlock(x, y);
}*/

// Draw blocks function!!!
void Window::drawBlocks()
{
  /*for(int i = 0; i < blocks.size(); i++)
    {
      blocks[i]->draw(renderer);
    }*/

}


void Window::drawWires()
{
	for (int i = 0; i < wires.size(); i++)
	{
		wires[i]->draw(renderer);
	}

}

void Window::drawAND(double x, double y)
{
	// Change color to blue
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

    // Set Trigonometry Values for drawing Half Circle
	double step = 2;					// step size= 2 degrees
	int numPoints = int(180/step + 3);	// number of points based on step size
	short xPoints[numPoints];			
	short yPoints[numPoints];

	double theta = 270*PI/180;					// start theta=270 degrees and convert to radians
	double xCenter = x + staticGateWidth;		// x value of center point for semi circle
	double yCenter = y + staticGateHeight/2;	// y value of center point for semi circle
	double radius = staticGateHeight/2;			// radius of semi circle
		
	for (int i=0; i<(180/step); i++) {				// loop through number of points
		xPoints[i] = xCenter + radius*cos(theta);	// get x value based on theta, xCenter, and radius
		yPoints[i] = yCenter + radius*sin(theta);	// get y value based on theta, yCenter, and radius
		theta += step*PI/180;						// increment theta by step size, convert to radians
	}

	xPoints[numPoints-3] = x+staticGateWidth;		// these points are for the rectangle
	yPoints[numPoints-3] = y+staticGateHeight;		// attached to the semi circle
	xPoints[numPoints-2] = x;
	yPoints[numPoints-2] = y+staticGateHeight;
	xPoints[numPoints-1] = x;
	yPoints[numPoints-1] = y;

	// lines, to represent ports
	boxRGBA(renderer, x, y+staticGateHeight/4-staticLineLength, x-staticGateWidth/3, 
		y+staticGateHeight/4+staticLineLength, 255, 0, 50, 255);
	boxRGBA(renderer, x, y+3*staticGateHeight/4-staticLineLength, x-staticGateWidth/3, 
		y+3*staticGateHeight/4+staticLineLength, 255, 0, 50, 255);
	boxRGBA(renderer, x+(staticGateWidth)+(staticGateHeight/2)+(staticGateWidth/3), 
		y+(staticGateHeight/2)-(staticLineLength), x+(staticGateWidth)+(staticGateHeight/2),
		y+(staticGateHeight/2)+(staticLineLength),255, 0, 50, 255);

	// draw body of AND gate as a single polygon
	filledPolygonRGBA(renderer, xPoints, yPoints, numPoints, 255, 0, 50, 255);
}

void Window::drawOR(double x, double y) 
{
	// Change color to blue
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

    // Set Trigonometry Values for drawing Half Circle
	double step = 2;					// step size= 2 degrees
	int numPoints = int(180/step*2 + 4);	// number of points based on step size
	short xPoints[numPoints];			
	short yPoints[numPoints];

	double theta = 270*PI/180;					// start theta=270 degrees and convert to radians
	double xCenter = x;							// x value of center point for semi circle
	double yCenter = y + staticGateHeight/2;	// y value of center point for semi circle
	double radius = staticGateHeight/2;			// radius of semi circle
	
	xPoints[0] = x;
	yPoints[0] = y;	
	for (int i=1; i<=(180/step); i++) {				// loop through number of points
		xPoints[i] = xCenter + radius*cos(theta);	// get x value based on theta, xCenter, and radius
		yPoints[i] = yCenter + radius*sin(theta);	// get y value based on theta, yCenter, and radius
		theta += step*PI/180;						// increment theta by step size, convert to radians
	}

	xPoints[91] = x;							// these points are for the rectangle
	yPoints[91] = y+staticGateHeight;			// attached to the semi circle
	xPoints[92] = x+(staticGateWidth);
	yPoints[92] = y+staticGateHeight;

	theta = 270*PI/180;						// reset theta
	xCenter = x + staticGateWidth;			// reset xCenter
	yCenter = y + (staticGateHeight/2);		// reset yCenter
	radius = staticGateHeight/2;			// reset radius

	for (int i=(numPoints-2); i>(92); i--) {			// loop through number of points
		xPoints[i] = xCenter + radius*cos(theta);		// get x value based on theta, xCenter, and radius
		yPoints[i] = yCenter + radius*sin(theta);		// get y value based on theta, yCenter, and radius
		theta += step*PI/180;							// increment theta by step size, convert to radians
	}
	
	xPoints[numPoints-1] = x+(staticGateWidth);
	yPoints[numPoints-1] = y;

	// lines, to represent ports
	boxRGBA(renderer, x+12, y, x-staticGateWidth/3, 
		y+2*staticLineLength, 255, 0, 50, 255);
	boxRGBA(renderer, x+12, y+staticGateHeight-2*staticLineLength, x-staticGateWidth/3, 
		y+staticGateHeight, 255, 0, 50, 255);
	boxRGBA(renderer, x + staticGateWidth + radius + (staticGateWidth/3), 
		y+(staticGateHeight/2)-(staticLineLength), x + staticGateWidth + radius,
		y+(staticGateHeight/2)+(staticLineLength),255, 0, 50, 255);

	// draw body of OR gate as a single polygon
	filledPolygonRGBA(renderer, xPoints, yPoints, numPoints, 255, 0, 50, 255);
}

void Window::drawNOT(double x, double y) 
{
	// Change color to blue
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

    // draw lines
    	boxRGBA( renderer, x, y+(staticGateHeight/2-staticLineLength), x-staticGateWidth/3, 
    		y+(staticGateHeight/2)+staticLineLength, 255, 0, 50, 255 );
    	boxRGBA( renderer, x+(2*staticGateWidth/3)+(staticGateWidth/3)-5, y+(staticGateHeight/2-staticLineLength), 
    		x+(2*staticGateWidth/3)-10, y+(staticGateHeight/2)+staticLineLength, 255, 0, 50, 255 );
    // draw triangle
	filledTrigonRGBA( renderer, x, y+(staticGateHeight/4), x+(2*staticGateWidth/3), 
		y+(staticGateHeight/2), x, y+(3*staticGateHeight/4), 255, 0, 50, 255);
}
