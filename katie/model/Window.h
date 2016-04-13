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
	staticGateWidth=60;
	staticGateHeight=40;
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
    double w=50;
    double h=60;
    //AND gate
    double x = viewController.x + (viewController.w / 2) - (staticGateWidth/2);
	double y = viewController.y + (viewController.h / 6) - (staticGateHeight/2);
	double step = 15;
	int numPoints = int(180/step + 2);
	short xPoints[numPoints];
	short yPoints[numPoints];

	double theta = 270*PI/180;
	double xCenter = x + w;
	double yCenter = y + h/2;
	double radius = h/2;
	
	for (int i=0; i<(180/step); i++) {
		xPoints[i] = xCenter + radius*cos(theta);
		yPoints[i] = yCenter + radius*sin(theta);
		theta += step*PI/180;
	}

	xPoints[numPoints-2] = x;
	yPoints[numPoints-2] = y+h;
	xPoints[numPoints-1] = x;
	yPoints[numPoints-1] = y;
	xPoints[numPoints] = xCenter + radius*cos(270*PI/180);
	yPoints[numPoints] = yCenter + radius*sin(270*PI/180);

	/*double xstart = x + w;
	double ystart = y + h;
	for( int i = 0; i < (w/2); i++ ){
		xPoints[i] = xstart + i;
		yPoints[i] = ystart - (h/w) * i;
	}
	int count = 0;
	for( int i = w/2; i < w; i++){
		xPoints[i] = x + (1.5*w) - count;
		yPoints[i] = y + (h/2) - (h/w)*count;
		count++;
	}
	xPoints[int(w+1)] = x;
	yPoints[int(w+1)] = y;
	xPoints[int(w+2)] = x;
	yPoints[int(w+2)] = y+h;*/
	filledPolygonRGBA(renderer, xPoints, yPoints, numPoints, 255, 0, 50, 255);
	//OR gate
	int x1 = viewController.x + (viewController.w / 2) - (staticGateWidth/2);
	int y1 = viewController.y + (3*viewController.h / 6) - (staticGateHeight/2);
	short x1Points[9] = {x1,x1,x1+50,x1+65,x1+70,x1+75,x1+70,x1+65,x1+50};
	short y1Points[9] = {y1,y1+60,y1+60,y1+50,y1+40,y1+30,y1+20,y1+10,y1};
	filledPolygonRGBA(renderer, x1Points, y1Points, 9, 255, 0, 50, 255);
	//Not gate
	int x2 = viewController.x + (viewController.w / 2) - (staticGateWidth/2);
	int y2 = viewController.y + (5*viewController.h / 6) - (staticGateHeight/2);
	short x2Points[9] = {x2,x2,x2+50,x2+65,x2+70,x2+75,x2+70,x2+65,x2+50};
	short y2Points[9] = {y2,y2+60,y2+60,y2+50,y2+40,y2+30,y2+20,y2+10,y2};
	filledPolygonRGBA(renderer, x2Points, y2Points, 9, 255, 0, 50, 255);

    /*SDL_RenderFillRect( renderer, &staticAND );
    SDL_RenderFillRect( renderer, &staticOR );
    SDL_RenderFillRect( renderer, &staticNOT );*/

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

