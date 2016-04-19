// logicCircuitDesign

// Window.h

// contains all of the information for the window


#include <SDL.h>
#include "SDL2_gfxPrimitives.h"
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include "Block.h"
#include "Gate.h"
#include "Input.h"
#include "Output.h"
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
		int snapWire(int, int);
		void deleteWire(int);
		void moveBlock(int);
		void drawBlocks();
		void drawWires();
		bool staticAndGateDetection( SDL_Event );
		bool staticOrGateDetection( SDL_Event );
		bool staticNotGateDetection( SDL_Event );
		bool gateDetection( int, SDL_Event );

		bool wireDetection( int );

		bool inputDetection( int, SDL_Event );
		void changeInputValue( int );


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

	// Sets 3 Static Input Blocks
	Block* Bptr;
	Bptr = new Input(50, 275, 'a', 0);
	blocks.push_back(Bptr);

	Bptr = new Input(50, 350, 'b', 0);
	blocks.push_back(Bptr);

	Bptr = new Input(50, 425, 'c', 0);
	blocks.push_back(Bptr);

	// Sets Static Output Block
	Bptr = new Output(690, 350, 'z', 0);
	blocks.push_back(Bptr);
	
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
	delete ptr;

	ptr = new OrGate(staticORx,staticORy);
	ptr -> draw(renderer);
	delete ptr;


	ptr = new NotGate(staticNOTx,staticNOTy);
	ptr -> draw(renderer);
	delete ptr;

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
			else if(x>logicCanvas.x && x<(logicCanvas.x+logicCanvas.w) 
					&& y>logicCanvas.y && y<(logicCanvas.y+logicCanvas.h))
			{	
				cout << "pressed in logic canvas" << endl;
				// determine if on wire
				for (int j = 0; j < wires.size(); j++)
				{
					if (wireDetection(j))
					{
						cout << "clicked on wire" << endl;
						break;
					}
				}

				// determine if on block
				for(int i = 0; i < blocks.size(); i++) {
					if (inputDetection(i, e)) {
							blockNum=i;
							action=3;
							break;
						}
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
					//for (int i = 0; i < blocks.size(); i++)
					//{
					//	int port = blocks[i]->onPort(x, y);
					//	if (port == 0)
					//	{
					makeWire();
					action = 1;
					break;
					//	}

					//}
				}
			}
			break;

		case SDL_MOUSEBUTTONUP:
			if (action == 1)
			{
				cout << "move it"<< endl;
				action = 0;
				moveWire();
			}
			else
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
		case 3:
			changeInputValue(blockNum);
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
	Wire* ptr = new Wire(x, y); // call constructor

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


void Window::moveWire()
{
	int x;
	int y;
	SDL_GetMouseState(&x, &y);
	wires.back()->movePoint2(x, y);

	if (action != 1)
	{
		// set wire
		if (!snapWire(x, y))
		{
		    wires.pop_back();
		    cout << "think about deleting that wire." << endl;

		}
	}
}

void Window::moveBlock(int i)
{
	int x;
	int y;

	// move block
	SDL_GetMouseState(&x,&y);
	blocks[i]->setx(x - dx);
	blocks[i]->sety(y - dy);

	// move wires
	blocks[i]->bringWires();

}


int Window::snapWire(int x, int y)
{
	int connections = 0; // number of snaps
	int port;  // -1 = none; 0 = output; 1,2,+ = input
	int highPortNum;
	short* point1;

	map<int, Block*> blockPorts;

	// Step 1) find connections:
	for (int i = 0; i < blocks.size(); i++)
	{
		port = blocks[i]->onPort(x, y);
		if (port >= 0)
		{
			blockPorts[port]=blocks[i];
			if (port > 0)
				highPortNum = port;
			break;
		}
	}
	for (int i = 0; i < blocks.size(); i++)
	{
		point1 = wires.back()->getPointXY(1); // retrieve wire coordinates from pt 2
		port = blocks[i]->onPort(point1[0], point1[1]);
		if (port >= 0)
		{
			blockPorts[port]=blocks[i];
			if (port > 0)
				highPortNum = port;
			break;
		}
	}

	// Step 2) stop connection errors:
	if (blockPorts.size() != 2)
	{
		cout << "not enough connections or connected to same port" << endl;
		return 0; // not 2 points on ports or 2 points on same port type
	}
	else if (blockPorts.count(0) <= 0) 
	{
		cout << "must connect to an outgoing port." << endl;
		return 0;
	}
	else if (blockPorts.begin()->second == blockPorts.rbegin()->second)
	{
		cout << "must connect to different objects." << endl;
		return 0;
	}
	else // wire connection is sound
	{
		// Step 3) connect visually
		// move front of wire to outPort of Block
		wires.back()->movePoint1(blockPorts[0]->getPortXY(0)[0], 
				blockPorts[0]->getPortXY(0)[1]);

		// move back of wire to correct inPort of Block
		wires.back()->movePoint2(blockPorts[highPortNum]->getPortXY(highPortNum)[0], 
				blockPorts[highPortNum]->getPortXY(highPortNum)[1]);

		// Step 4) connect pointers
		// point wire pointer backward to block address
		wires.back()->setBackwardPtr(blockPorts[0]);

		// point block pointer (1 or 2) backward to wire address
		blockPorts[highPortNum]->setPortPtr(highPortNum, wires.back());

		// point wire pointer forward to next block address (1 or 2)
		wires.back()->setForwardPtr(blockPorts[highPortNum]);

		// point previous block pointer (out) forward to
		blockPorts[0]->setPortPtr(0, wires.back());
	}
	return 1;
}


void Window::deleteWire(int wireNum)
{
	delete wires[wireNum];
	wires.erase(wires.begin()+wireNum);

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


bool Window::wireDetection( int wireNum)
{

	return false;
}


bool Window::inputDetection( int blockNum, SDL_Event event ) 
{
	double blockX = blocks[blockNum]->getx();
	double blockY = blocks[blockNum]->gety();

	if((event.motion.x>50) && (event.motion.x<80)){
		if ( (event.motion.y>275) && (event.motion.y < 305)) {
			return true;
		}
		else if((event.motion.y>350) && (event.motion.y < 380)){
			return true;
		}
		else if((event.motion.y>425) && (event.motion.y<455)) {
			return true;
		}
	}
	return false;
}

void Window::changeInputValue( int i )
{
	blocks[i]->setValue();
	cout << blocks[i]->getValue() << endl;
}

