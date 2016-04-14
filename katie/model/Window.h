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
#include "AndGate.h"
#include "OrGate.h"
#include "NotGate.h"

#define PI 3.14159265

class Window {

	public:
		Window();
		~Window();

		int init();
		void draw();
		int eventHandler(SDL_Event);

		void makeWire();
		void makeBlock(int);
		void moveWire();
		//void moveBlocks();
		void drawBlocks();
		void drawWires();
		bool andGateDetection( SDL_Event );
		bool orGateDetection( SDL_Event );
		bool notGateDetection( SDL_Event );

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
		double buffer;
		double highlightBoxWidth;
		double highlightBoxHeight; 
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
	buffer = 2;
	highlightBoxWidth = (5/3)*staticGateWidth + (1/2)*staticGateHeight + 2*buffer;
	highlightBoxHeight = staticGateHeight + 2*buffer;

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
    double x = viewController.x + (viewController.w / 2) - (staticGateWidth+(staticGateHeight/2))/2;
	double y = viewController.y + (viewController.h / 6) - (staticGateHeight/2);
	
	Block* ptr = new AndGate(x,y);
	ptr -> draw(renderer);

	//OR gate
	int x1 = viewController.x + (viewController.w / 2) - (staticGateWidth+(staticGateHeight/2))/2;
	int y1 = viewController.y + (3*viewController.h / 6) - (staticGateHeight/2);

	ptr = new OrGate(x1,y1);
	ptr -> draw(renderer);

	//Not gate
	int x2 = viewController.x + (viewController.w / 2) - (staticGateWidth/3);
	int y2 = viewController.y + (5*viewController.h / 6) - (staticGateHeight/2);
	
	ptr = new NotGate(x2,y2);
	ptr -> draw(renderer);

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
		  int x,y;
		  SDL_GetMouseState(&x, &y);

		  //check if mouse is inside a selection
		  	if (andGateDetection( e )) {
                makeBlock(0); //0 = AND
            }
            else if (orGateDetection( e )) {
              	makeBlock(1); //1 = OR
            }
            else if (notGateDetection( e )) {
                makeBlock(2); //2 = NOT
            }
	
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

void Window::makeBlock(int i)
{
	SDL_Event e;
	int x,y;


	while(SDL_WaitEvent(&e) >= 0 ){
		if(e.type = SDL_MOUSEBUTTONUP){
			if(e.type = SDL_MOUSEBUTTONDOWN){
				SDL_GetMouseState(&x, &y);
				if(x>logicCanvas.x && x<(logicCanvas.x+logicCanvas.w) && y>logicCanvas.y && y<(logicCanvas.y+logicCanvas.h)){
					break;
				}
			}
		}		

	}

	Block* Bptr;

	if( i == 0 ){
		Bptr = new AndGate(x,y);
	}
	else if(i == 1){
		
		Bptr = new OrGate(x,y);
	}
	else if(i == 2){
		
		Bptr = new NotGate(x,y);
	}
	
	
	
	
	blocks.push_back(Bptr);
	action = 0;
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
  for(int i = 0; i < blocks.size(); i++)
    {
      blocks[i]->draw(renderer);
    }

}


void Window::drawWires()
{
	for (int i = 0; i < wires.size(); i++)
	{
		wires[i]->draw(renderer);
	}

}

bool Window::andGateDetection( SDL_Event event) 
{
	 if ( (event.motion.x>staticAND.x) && (event.motion.x<(staticAND.x+staticAND.w)) ) {
        if ( (event.motion.y>staticAND.y) && (event.motion.y<(staticAND.y+staticAND.h)) ) {
            return true;
        }
    }
    return false;
	/*double xBound = x - (highlightBoxWidth/2);
	double yBound = y - (highlightBoxHeight/2);
    if ( (event.motion.x>xBound) && (event.motion.x<(xBound+highlightBoxWidth)) ) {
        if ( (event.motion.y>yBound) && (event.motion.y<(yBound+highlightBoxHeight)) ) {
            return true;
        }
    }
    return false;*/
}
bool Window::orGateDetection( SDL_Event event ) 
{
    if ( (event.motion.x>staticOR.x) && (event.motion.x<(staticOR.x+staticOR.w)) ) {
        if ( (event.motion.y>staticOR.y) && (event.motion.y<(staticOR.y+staticOR.h)) ) {
            return true;
        }
    }
    return false;
}
bool Window::notGateDetection( SDL_Event event ) 
{

    if ( (event.motion.x>staticNOT.x) && (event.motion.x<(staticNOT.x+staticNOT.w)) ) {
        if ( (event.motion.y>staticNOT.y) && (event.motion.y<(staticNOT.y+staticNOT.h)) ) {
            return true;
        }
    }
    return false;
}
