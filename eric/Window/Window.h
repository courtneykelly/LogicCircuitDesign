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

	void makeWire(int);
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


void Window::action(SDL_Event e)
{
	switch(e.type)
	{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			cout << "makeWire" << endl;
			makeWire(1);
			break;
		case SDL_MOUSEBUTTONUP:
			cout << "makeWire" << endl;
			makeWire(0);
			break;
	}
}


void Window::makeWire(int newWire)
{
	int x;
	int y;
    SDL_GetMouseState(&x, &y);
	if (action != 1 && newWire)
	{
		Wire* ptr = new Wire(NULL, x, y); // call constructor

		wires.push_back(ptr);
		action = 1;
	}
	else if (action == 1)
	{
		wires.back()->movePoint(x, y);
		action = 0;
	}
}

void Window::drawWires()
{
	for (int i = 0; i < wires.size(); i++)
	{
		cout << "Drawing " << i << endl;
		wires[i]->draw(renderer);
	}
}

