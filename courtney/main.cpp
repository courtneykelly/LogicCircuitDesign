#include "SDL.h"
#include <iostream>

int posX = 100;
int posY = 200;
int sizeX = 300;
int sizeY = 400;

SDL_Window* window;
SDL_Renderer* renderer;

bool InitEverything();
bool InitSDL();
bool CreateWindow();
bool CreateRenderer();
void SetupRenderer();

void Render();
void RunGame();

SDL_Rect playerPos;

int main( int argc, char* args[] )
{
    if ( !InitEverything() ) 
        return -1;


    // Initlaize our playe
    playerPos.x = 20;
    playerPos.y = 20;
    playerPos.w = 20;
    playerPos.h = 20;

    RunGame();
}
void Render()
{
    // Clear the window and make it all green
    SDL_RenderClear( renderer );

    // Change color to blue
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

    // Render our "player"
    SDL_RenderFillRect( renderer, &playerPos );

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
    window = SDL_CreateWindow( "Logic Canvas", posX, posY, sizeX, sizeY, 0 );

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
                    playerPos.x = event.motion.x - (playerPos.h/2);
                    playerPos.y = event.motion.y - (playerPos.w/2);
                   
            }
        }

        Render();

        // Add a 16msec delay to make our game run at ~60 fps
        SDL_Delay( 16 );
    }
}