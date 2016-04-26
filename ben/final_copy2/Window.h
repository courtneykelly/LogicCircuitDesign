/* 	logicCircuitDesign
	Window.h
	contains all of the information for the window
*/

#include <SDL.h>
#include "SDL2_gfxPrimitives.h"
#include <SDL2/SDL_image.h>
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
		bool loadFromFile();
		int eventHandler(SDL_Event);

		void makeWire();
		void makeBlock( int );
		void moveWire();
		int snapWire( int, int );
		void deleteWire( int );
		void moveBlock( int );
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

		SDL_Rect title;
		SDL_Texture* titleText;
		int titleWidth;
		int titleHeight;

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


/* 	Constructor
*/
Window::Window()
{
	// Initialize Important Variables for Window dimensions
	screen_width = 1000;	// window width
	screen_height = 600;	// window height
	window = NULL;
	renderer = NULL;
	titleText = NULL;
	titleHeight = 100;
	titleWidth = 650;
	action = 0;				// type of drawing action: wire, gate, or input
	borderSize=10;			// border size between canvases
	staticGateWidth=50;		// width of the static gates in the View Controller Canvas on right
	staticGateHeight=60;	// height of the static gates in the View Controller Canvas on right
	staticLineLength=1;		// length of output port lines
	buffer = 2;
	highlightBoxWidth = (5/3)*staticGateWidth + (1/2)*staticGateHeight + 2*buffer;	// highlight box is the clicking range for a 
	highlightBoxHeight = staticGateHeight + 2*buffer;								// gate detection in the view controller


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

	// Initialize title image
	title.x = 0;
	title.y = 0;
	title.w = titleWidth;
	title.h = titleHeight;

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

	init();	// call init function
}


/* 	Destructor
	Destroys everything in the window, this function is called during 
	an exit click event in order to exit the window.
*/
Window::~Window()
{
	SDL_DestroyRenderer (renderer);
	SDL_DestroyWindow (window);
	window = NULL;
	renderer = NULL;

	SDL_Quit();
}


/* 	Initilaizes the window and renderer
*/
int Window::init()
{
	// Error handling, if for some reason SDL couldn't initialize 
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Could not initialize SDL: " << SDL_GetError() << std::endl;
		return -1;
	}

	// Create window
	window = SDL_CreateWindow("Logic Circuit Design", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);

	// Create renderer
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL)
	{
		std::cout << "Could not create renderer: " << SDL_GetError() << std::endl;
		return -1;
	}

	//Load images
	loadFromFile();

	// Set renderer resolution
	SDL_RenderSetLogicalSize (renderer, screen_width, screen_height);

	// set Background color
	SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
	SDL_RenderClear (renderer);

	return 1;
}

/*	Draw function. This function draws everything that is static on the 
	window. This includes the three static gates in the View Controller, 
	the View Controller box itself, and the logic canvas box. This function 
	needs to be constantly called in our main as everything changes as the 
	user interacts with it, but our background stays the same.
*/
void Window::draw()
{
	// Change color to blue
	SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

	// Draws Static Gates
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

	//Draw image
	SDL_RenderCopy( renderer, titleText, NULL, &title);


	SDL_RenderPresent(renderer); // draws it
	SDL_Delay(40); // 40 default
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer); // clear screen to white

}

bool Window::loadFromFile() {
	SDL_Surface* loadedSurface = IMG_Load("Title.bmp");
	if( loadedSurface == NULL )
	{
		cout << "Unable to load image.";
	}
	else {
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ));
		titleText = SDL_CreateTextureFromSurface( renderer, loadedSurface);
		if( titleText == NULL )
		{
			cout << "Unable to create texture.";
		}
		else {
			titleWidth = loadedSurface->w;
			titleHeight = loadedSurface->h;
		}
	}

	SDL_FreeSurface( loadedSurface);
	return titleText != NULL;
}

/*	Event Handler function. Conditionally calls actions based on SDL 
	event and variables. This function is how the user interacts with 
	the program. The user performs an SDL event such as a click, or a
	drag, and we call the appropriate function for our prgram to react 
	accordingly. 
*/
int Window::eventHandler(SDL_Event e)
{
	// cout << "e.type: " << e.type << endl;
	switch(e.type)
	{
		case SDL_QUIT:
			return 1; // quits
			break;
		case SDL_MOUSEBUTTONDOWN:		// If the user clicks down without releasing
			
			double blockX, blockY;

			// Checks if mouse is inside one of the static gates
			// Draws the apprpriate gate on the logic canvas
			if (staticAndGateDetection( e )) {
				makeBlock(0); //0 = AND
			}
			else if (staticOrGateDetection( e )) {
				makeBlock(1); //1 = OR
			}
			else if (staticNotGateDetection( e )) {
				makeBlock(2); //2 = NOT
			}
			// This "else if" handles clicks within the logic canvas. These types of actions
			// could be a wire draw, moving one of the gates on the canvas, or changing
			// the value of one of the input blocks
			else if(e.motion.x>logicCanvas.x && e.motion.x<(logicCanvas.x+logicCanvas.w) 
					&& e.motion.y>logicCanvas.y && e.motion.y<(logicCanvas.y+logicCanvas.h))
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

				// determine if on input or gate block
				for(int i = 0; i < blocks.size(); i++) {
					blocks[i]->onBlock(e.motion.x, e.motion.y);

					if (inputDetection(i, e)) {
							blockNum=i;
							action=3;
							break;
						}
					if(gateDetection(i, e)) {
						if(blocks[i]->getx() == 50){
							action = 0;
							break;
						}
						cout << "gate detection!!" << endl;
						blockNum = i;
						dx = e.motion.x - blocks[i]->getx();
						dy = e.motion.y - blocks[i]->gety();
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

	// Performs appropriate action based on click event
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


/* 	Push back a new wire to vector wires
*/
void Window::makeWire()
{
	int x;
	int y;
	SDL_GetMouseState(&x, &y);
	Wire* ptr = new Wire(x, y); // call constructor

	wires.push_back(ptr);		// add wireto vector of pointers
	action = 1;
}

/*	Pushback a new Gate based on it's type, which is passed as an integer 
	to the function. 0 is a new AND gate, 1 is a new OR gate, and 2 is a 
	new NOT gate.
*/
void Window::makeBlock(int i)
{
	int x, y;
	Block* Bptr;

	if( i == 0 ){
		x = 100;
		y = 300;
		Bptr = new AndGate(x,y);	// create new pointer and call AND gate constructor
	}
	else if(i == 1){
		x = 100;
		y = 400;
		Bptr = new OrGate(x,y);		// create new pointer and call OR gate constructor
	}
	else if(i == 2){
		x = 100;
		y = 500;
		Bptr = new NotGate(x,y);	// create new pointer and call NOT gate constructor
	}


	blocks.push_back(Bptr);		// push the new point into the vector of pointers for the blocks
	action = 0;
}

/*	This function handles the moving of wires. This happens when you want to 
	click and drag a wire. It gets the wire you've created or are moving and has
	the endpoint of that wire follow the x and y position of the mouse to create
	the click and drag effect. It will then snap the wire into a port position or 
	delete it if it's in an incorrect position.
*/
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
			delete wires.back();
		    wires.pop_back(); // deletes last wire
		    cout << "think about deleting that wire." << endl;

		}
	}
}
	
/*	This function moves the gate you're clicking on.
	Once you click on it the position of the gate will
	follow the x and y coordinates of the mouse. It also calls
	the bringWires function to make sure if there is a wire
	attached to a port oin the gate you're moving, it follows.
*/
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

/*	The function gives the effect of snapping a wire into postion.
	If you click and drag a wire to a port, we wanted it to snap to the 
	exact position of the port, once you were in circle range of that port.
*/
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
	else if (blockPorts[highPortNum]->getPortPtr(highPortNum) != NULL)
	{
		cout << "in ports must not already have connections" << endl;
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

/*	This function will erase a wire. This happens when you click and drag a 
	wire to an incorrect port, or to no port at all.	
*/
void Window::deleteWire(int wireNum)
{
	delete wires[wireNum];
	wires.erase(wires.begin()+wireNum);
}


/*	This function loops through our blocks vector of pointers to gates objects,
	input objects, and output objects.
*/
void Window::drawBlocks()
{
	for(int i = 0; i < blocks.size(); i++)
	{
		blocks[i]->draw(renderer);
	}
}

/*	This function loops through out wires vector of pointer to wire objects.
	This vector stores all the wires that are currently drawn on the 
	screen. We call this function in main, so it constantly redraws the wires.
	This is to handle when we move wires, or click and drag them, etc.
*/
void Window::drawWires()
{
	for (int i = 0; i < wires.size(); i++)
	{
		wires[i]->draw(renderer);
	}

}

/*	This function returns true if the user clicked on the static AND gate in 
	the view controller. We use this function, so if the user clicks on a static 
	AND gate, then a new one will be drawn on the logic canvas.
*/
bool Window::staticAndGateDetection( SDL_Event event) 
{
	if ( (event.motion.x>staticANDx) && (event.motion.x<(staticANDx+highlightBoxWidth)) ) {
		if ( (event.motion.y>staticANDy) && (event.motion.y<(staticANDy+highlightBoxHeight)) ) {
			return true;
		}
	}
	return false;
}

/*	This function returns true if the user clicked on the static OR gate in 
	the view controller. We use this function, so if the user clicks on a static 
	OR gate, then a new one will be drawn on the logic canvas.
*/
bool Window::staticOrGateDetection( SDL_Event event ) 
{
	if ( (event.motion.x>staticORx) && (event.motion.x<(staticORx+highlightBoxWidth)) ) {
		if ( (event.motion.y>staticORy) && (event.motion.y<(staticORy+highlightBoxHeight)) ) {
			return true;
		}
	}
	return false;
}

/*	This function returns true if the user clicked on the static NOT gate in 
	the view controller. We use this function, so if the user clicks on a static 
	NOT gate, then a new one will be drawn on the logic canvas.
*/
bool Window::staticNotGateDetection( SDL_Event event ) 
{

	if ( (event.motion.x>staticNOTx) && (event.motion.x<(staticNOTx+highlightBoxWidth)) ) {
		if ( (event.motion.y>staticNOTy) && (event.motion.y<(staticNOTy+highlightBoxHeight)) ) {
			return true;
		}
	}
	return false;
}

/*	This function returns true if the user clicked on one of the gates on the logic canvas.
	We loop through this funciton in our Event Handler. We loops through our blocks vector
	of pointers and pass in the block number we are looking at, along with the SDL event. It 
	sees if the SDL click event corresponds to one of the blocks on the logic canvas. If 
	this is true, we'll return true in order to enable movement of that block.
*/
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

/*	This function is not used in the Window class, but it needed to be implemented
	because it is a virtual function.
*/
bool Window::wireDetection( int wireNum)
{
	return false;
}

/*	This function detects if one of the input blocks has been clicked. This is 
	necessary because if one of the input blocks has been clicked then 
	we need to change its value. 
*/
bool Window::inputDetection( int blockNum, SDL_Event event ) 
{
	double blockX = blocks[blockNum]->getx();
	double blockY = blocks[blockNum]->gety();

	if((event.motion.x>blockX) && (event.motion.x<(blockX+30))){
		if ( (event.motion.y>blockY) && (event.motion.y < (blockY+30))) {
			return true;
		}
	}
}

/*	This function changes the value of the input blocks by calling 
	the set value funtion of the Input.h class.
*/
void Window::changeInputValue( int i )
{
	blocks[i]->setValue();
	cout << blocks[i]->getValue() << endl;
}


