#include "SDL.h"
#include <iostream>

using namespace std;

int posX = 50;
int posY = 70;
int sizeX = 1000;
int sizeY = 700;
int borderSize = 10;
int staticGateWidth = 60;
int staticGateHeight = 40; 

SDL_Window* window;
SDL_Renderer* renderer;

bool InitEverything();
bool InitSDL();
bool CreateWindow();
bool CreateRenderer();
void SetupRenderer();

void Render();
void RunGame();
bool andGateDetection( SDL_Event );
bool orGateDetection( SDL_Event );
bool notGateDetection( SDL_Event );

SDL_Rect viewController;
SDL_Rect logicCanvas;
SDL_Rect staticAND;
SDL_Rect staticOR;
SDL_Rect staticNOT;

int main( int argc, char* args[] )
{
    if ( !InitEverything() ) 
        return -1;

    // Initialize View Controller
    viewController.x = sizeX - (sizeX/4);
    viewController.y = sizeY/2;
    viewController.w = sizeX/4 - borderSize;
    viewController.h = sizeY/2 - borderSize;

    // Initialize Logic Canvas
    logicCanvas.x = borderSize;
    logicCanvas.y = sizeY/3;
    logicCanvas.w = sizeX - (3*borderSize) - (viewController.w);
    logicCanvas.h = 2*sizeY/3 - borderSize;

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

    RunGame();
}

void Render()
{
    // Clear the window and make it all green
    SDL_RenderClear( renderer );

    // Change color to blue
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

    // Draw Static Gates
    SDL_RenderFillRect( renderer, &staticAND );
    SDL_RenderFillRect( renderer, &staticOR );
    SDL_RenderFillRect( renderer, &staticNOT );

    // Draw Rectangle for View Controller
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );     // Change Color to Black
    SDL_RenderDrawRect( renderer, &viewController );
    SDL_RenderDrawRect( renderer, &logicCanvas );

    // Change color to white
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );

    // Render the changes above
    SDL_RenderPresent( renderer);
}
bool InitEverything()
{
    if ( !InitSDL() )
        return false;

    if ( !CreateWindow() )
        return false;

    if ( !CreateRenderer() )
        return false;

    SetupRenderer();

    return true;
}
bool InitSDL()
{
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}
bool CreateWindow()
{
    window = SDL_CreateWindow( "Logic Circuit Design Simulator", posX, posY, sizeX, sizeY, 0 );

    if ( window == nullptr )
    {
        std::cout << "Failed to create window : " << SDL_GetError();
        return false;
    }

    return true;
}
bool CreateRenderer()
{
    renderer = SDL_CreateRenderer( window, -1, 0 );

    if ( renderer == nullptr )
    {
        std::cout << "Failed to create renderer : " << SDL_GetError();
        return false;
    }

    return true;
}
void SetupRenderer()
{
    // Set size of renderer to the same as window
    SDL_RenderSetLogicalSize( renderer, sizeX, sizeY );

    // Set color of renderer to green
    SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
}
void RunGame()
{
    bool loop = true;

    while ( loop )
    {
        SDL_Event event;
        while ( SDL_PollEvent( &event ) )
        {
            if ( event.type == SDL_QUIT )
                loop = false;
            else if ( event.type == SDL_MOUSEBUTTONDOWN )
            {
                if (andGateDetection( event )) {
                    cout << "And Gate Detection" << endl;
                }
                else if (orGateDetection( event )) {
                    cout << "OR Gate Detection" << endl;
                }
                else if (notGateDetection( event )) {
                    cout << "NOT Gate Detection" << endl;
                }
                   
            }
        }

        Render();

        // Add a 16msec delay to make our game run at ~60 fps
        SDL_Delay( 16 );
    }
}
bool andGateDetection( SDL_Event event ) 
{
    if ( (event.motion.x>staticAND.x) && (event.motion.x<(staticAND.x+staticAND.w)) ) {
        if ( (event.motion.y>staticAND.y) && (event.motion.y<(staticAND.y+staticAND.h)) ) {
            return true;
        }
    }
    return false;
}
bool orGateDetection( SDL_Event event ) 
{
    if ( (event.motion.x>staticOR.x) && (event.motion.x<(staticOR.x+staticOR.w)) ) {
        if ( (event.motion.y>staticOR.y) && (event.motion.y<(staticOR.y+staticOR.h)) ) {
            return true;
        }
    }
    return false;
}
bool notGateDetection( SDL_Event event ) 
{
    if ( (event.motion.x>staticNOT.x) && (event.motion.x<(staticNOT.x+staticNOT.w)) ) {
        if ( (event.motion.y>staticNOT.y) && (event.motion.y<(staticNOT.y+staticNOT.h)) ) {
            return true;
        }
    }
    return false;
}