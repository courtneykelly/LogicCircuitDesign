// logicCircuitDesign

// Window.h

// contains all of the information for the window


#include <SDL.h>
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include "Block.h"
	#include "Gate.h"
	#include "Input.h"
	#include "Wire.h"



class Window {

	public:
		Window();
		~Window();

		int init();
		void draw();
		int eventHandler(SDL_Event);

		void makeWire();
		void moveWire();
		void drawWires();

	private:
		int screen_width;
		int screen_height;
		SDL_Window* window;
		SDL_Renderer* renderer;
		vector<Wire*> wires;
		int action; // 0=none, 1=drawing wires, ...
};


// constructor
Window::Window()
{
    screen_width = 640;
    screen_height = 480;
    window = NULL;
    renderer = NULL;
	action = 0;
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
    window = SDL_CreateWindow("Logic Circuit Design", 
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
	screen_width, screen_height, SDL_WINDOW_SHOWN);

    // create renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
    {
		std::cout << "Could not create renderer: " << SDL_GetError() << std::endl;
		return -1;
    }

    // set renderer resolution
    SDL_RenderSetLogicalSize (renderer, screen_width, screen_height);

    // set Background color?
    SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);

    SDL_RenderClear (renderer);

    return 1;
}


void Window::draw()
{
    SDL_RenderPresent(renderer); // draws it
    SDL_Delay(40); // 40 default
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer); // clear screen to white
}


// Conditionally call actions based on SDL event and variables
int Window::eventHandler(SDL_Event e)
{
	switch(e.type)
	{
		case SDL_QUIT:
			return 1; // quits
			break;
		case SDL_MOUSEBUTTONDOWN:
			makeWire();
			break;
		case SDL_MOUSEBUTTONUP:
			action = 0;
			break;
	}
	
	switch (action)
	{
		case 1:
			moveWire();
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


void Window::moveWire()
{
	int x;
	int y;
	SDL_GetMouseState(&x, &y);
	wires.back()->movePoint(x, y);
}


void Window::drawWires()
{
	for (int i = 0; i < wires.size(); i++)
	{
		wires[i]->draw(renderer);
	}
}

