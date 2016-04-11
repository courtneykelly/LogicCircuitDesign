// logicCircuitDesign

// Window.h

// contains all of the information for the window


#include <SDL.h>
#include <string>
#include <iostream>
#include <cmath>


class Window {

    public:
	Window();
	~Window();

	int init();
	bool loadMedia();
	void close();
	void draw();

    private:
	int screen_width;
	int screen_height;
	SDL_Window* window;
	SDL_Renderer* renderer;
};


// constructor
Window::Window()
{
    screen_width = 640;
    screen_height = 480;
    window = NULL;
    renderer = NULL;
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
    SDL_RenderPresent(renderer);
    SDL_Delay(40);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderClear(renderer);
}



void Window::makeLine()
{
    SDL_GetMouseState



}

