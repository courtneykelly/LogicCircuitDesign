// logicCircuitDesign

// Window.h

// contains all of the information for the window


#include <SDL.h>
#include "SDL2_gfxPrimitives.h"
#include "SDL_image.h"
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
		void makeInputs();
		void moveWire();
		void moveBlock(int);
		void drawBlocks();
		void drawWires();
		bool staticAndGateDetection( SDL_Event );
		bool staticOrGateDetection( SDL_Event );
		bool staticNotGateDetection( SDL_Event );
		bool gateDetection( int, SDL_Event );

		bool LoadTexture( const string &str );	

	private:
		double screen_width;
		double screen_height;
		SDL_Window* window;
		SDL_Renderer* renderer;
		vector<Block*> blocks;
		vector<Wire*> wires;
		int action; // 0=none, 1=drawing wires, 2=moving blocks
		int blockNum;
		int dx;
		int dy;
		SDL_Rect viewController;
		SDL_Rect logicCanvas;
		// Textures
			SDL_Rect a0;
			SDL_Texture* a0Texture;
		int borderSize;
		double staticANDx;
		double staticANDy;
		double staticORx;
		double staticORy;
		double staticNOTx;
		double staticNOTy;
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

    staticANDx = viewController.x + (viewController.w / 2) - (staticGateWidth+(staticGateHeight/2))/2;
	staticANDy = viewController.y + (viewController.h / 6) - (staticGateHeight/2);

	staticORx = viewController.x + (viewController.w / 2) - (staticGateWidth+(staticGateHeight/2))/2;
	staticORy = viewController.y + (3*viewController.h / 6) - (staticGateHeight/2);

	staticNOTx = viewController.x + (viewController.w / 2) - (staticGateWidth/3);
	staticNOTy = viewController.y + (5*viewController.h / 6) - (staticGateHeight/2);

	// Initialize Input Images
		/*if(LoadTexture("player.bmp")) {
			cout << "Yay";
		}
		if(a0Texture == NULL) {
			cout << "\nBad\n";
		}

		a0.x = 100;
		a0.y = 400;
		a0.w = 118;
		a0.h = 118;*/

		

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
    
	
	Block* ptr = new AndGate(staticANDx,staticANDy);
	ptr -> draw(renderer);

	ptr = new OrGate(staticORx,staticORy);
	ptr -> draw(renderer);

	
	ptr = new NotGate(staticNOTx,staticNOTy);
	ptr -> draw(renderer);

	makeInputs();

    // Draw Rectangle for View Controller
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );     // Change Color to Black
    SDL_RenderDrawRect( renderer, &viewController );
    SDL_RenderDrawRect( renderer, &logicCanvas );
    //SDL_RenderDrawRect(renderer, &a0);


    // Load Images
    	SDL_RenderCopy( renderer, a0Texture, NULL, &a0 );

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
			double blockX, blockY;
			SDL_GetMouseState(&x, &y);

			//check if mouse is inside a selection
			if (staticAndGateDetection( e )) {
				makeBlock(0); //0 = AND
			}
			else if (staticOrGateDetection( e )) {
				makeBlock(1); //1 = OR
			}
			else if (staticNotGateDetection( e )) {
				makeBlock(2); //2 = NOT
			}
			else if(x>logicCanvas.x && x<(logicCanvas.x+logicCanvas.w) && y>logicCanvas.y && y<(logicCanvas.y+logicCanvas.h))
			{	
				cout << "pressed in logic canvas" << endl;
				for(int i = 0; i < blocks.size(); i++) {
					if(gateDetection(i, e)) {
						cout << "gate detection!!" << endl;
						blockNum = i;
						dx = x - blocks[i]->getx();
						dy = y - blocks[i]->gety();
						action = 2;
						break;
					}
				}
				if (action == 0)
				{
					makeWire();
					action = 1;
				}
			}
			break;

		case SDL_MOUSEBUTTONUP:
			action = 0;
			break;
	}

	//cout << "action: " << action;

	switch (action)
	{
		case 1:
			moveWire();
			break;
		case 2:
			moveBlock(blockNum);
			break;
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
	int x, y;
	Block* Bptr;

	if( i == 0 ){
		x = 100;
		y = 300;
		Bptr = new AndGate(x,y);
	}
	else if(i == 1){
		x = 100;
		y = 400;
		Bptr = new OrGate(x,y);
	}
	else if(i == 2){
		x = 100;
		y = 500;
		Bptr = new NotGate(x,y);
	}
	
	
	blocks.push_back(Bptr);
	action = 0;
}

void Window::makeInputs()
{
	double x = 100;
	double y = 400;
	int value = 0;
	Block* aPtr = new Input(x,y,'a',value);
	Block* bPtr = new Input(x,y,'b',value);
	Block* cPtr = new Input(x,y,'c',value);
	Block* zPtr = new Input(x,y,'z',value);
	blocks.push_back(aPtr);
	blocks.push_back(bPtr);
	blocks.push_back(cPtr);
	blocks.push_back(zPtr);
}

void Window::moveWire()
{
	int x;
	int y;
	SDL_GetMouseState(&x, &y);
	wires.back()->movePoint(x, y);
}

void Window::moveBlock(int i)
{
 	//SDL_Event e;
 	int x;
 	int y;
 	//SDL_PollEvent( &e );
 	//while( e.type != SDL_MOUSEBUTTONUP) {
  	SDL_GetMouseState(&x,&y);
 	blocks[i]->setx(x - dx);
  	blocks[i]->sety(y - dy);

  	//SDL_RenderPresent(renderer);
  	//blocks[i]->draw(renderer);
  	//SDL_PollEvent( &e );
	

}

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

bool Window::LoadTexture( const string &str ) 
{
	// Initialize to NULL
		SDL_Texture* texture = NULL;

	// Load Image as SD_Surface
		SDL_Surface* surface = SDL_LoadBMP( str.c_str() );
		if( surface == NULL ){
				cout << "\nUnable to load image.\n" << endl;
		}
		else {
				cout << "\ngot it";
		}

	// SDL_Surface is just the raw pixels 
	// Convert it to a hardware-optimized texture so we can render it
		texture = SDL_CreateTextureFromSurface( renderer, surface );
		if( texture == NULL ){
				cout << "\nUnable to create texture." << endl;
		}
		else {
				cout << "got texture";
		}

	// Don't need the original texture, release the memory
		SDL_FreeSurface( surface );
		a0Texture = texture;

	return a0Texture != NULL;
}

bool Window::staticAndGateDetection( SDL_Event event) 
{
	 if ( (event.motion.x>staticANDx) && (event.motion.x<(staticANDx+highlightBoxWidth)) ) {
        if ( (event.motion.y>staticANDy) && (event.motion.y<(staticANDy+highlightBoxHeight)) ) {
            return true;
        }
    }
    return false;
}
bool Window::staticOrGateDetection( SDL_Event event ) 
{
    if ( (event.motion.x>staticORx) && (event.motion.x<(staticORx+highlightBoxWidth)) ) {
        if ( (event.motion.y>staticORy) && (event.motion.y<(staticORy+highlightBoxHeight)) ) {
            return true;
        }
    }
    return false;
}
bool Window::staticNotGateDetection( SDL_Event event ) 
{

    if ( (event.motion.x>staticNOTx) && (event.motion.x<(staticNOTx+highlightBoxWidth)) ) {
        if ( (event.motion.y>staticNOTy) && (event.motion.y<(staticNOTy+highlightBoxHeight)) ) {
            return true;
        }
    }
    return false;
}

bool Window::gateDetection( int blockNum, SDL_Event event )
{
	double blockX = blocks[blockNum]->getx();
	double blockY = blocks[blockNum]->gety();

	if((event.motion.x>blockX) && (event.motion.x<(blockX + highlightBoxWidth))){
		if ( (event.motion.y>blockY) && (event.motion.y < (blockY + highlightBoxHeight))) {
			return true;
		}
	}

	return false;

}
