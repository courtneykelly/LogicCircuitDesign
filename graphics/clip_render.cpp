/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
  and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard math, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Button constants
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 180;
const int TOTAL_BUTTONS = 1;

enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_DOWN = 0,
	BUTTON_SPRITE_MOUSE_UP = 1,
	BUTTON_SPRITE_TOTAL = 2
};
 
//Texture wrapper class
class LTexture
{
public:
  //Initializes variables
  LTexture();

  //Deallocates memory
  ~LTexture();

  //Loads image at specified path
  bool loadFromFile( std::string path );

  //Deallocates texture
  void free();

  //Renders texture at given point
  void render( int x, int y, SDL_Rect* clip = NULL );

  //Gets image dimensions
  int getWidth();
  int getHeight();

private:
  //The actual hardware texture
  SDL_Texture* mTexture;

  //Image dimensions
  int mWidth;
  int mHeight;
};

//The mouse button
class LButton
{
	public:
		//Initializes internal variables
		LButton();
	
		//Sets top left position
		void setPosition( int x, int y );

		//Handles mouse event
		void handleEvent( SDL_Event* e );

	private:
		//Top left position
		SDL_Point mPosition;

		//Currently used global sprite
		LButtonSprite mCurrentSprite;
};


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene sprites
SDL_Rect gANDGATE;
LTexture gTexture;

//Button objects
LButton gButtons;

LTexture::LTexture()
{
  //Initialize
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

LTexture::~LTexture()
{
  //Deallocate
  free();
}

bool LTexture::loadFromFile( std::string path )
{
  //Get rid of preexisting texture
  free();

  //The final texture
  SDL_Texture* newTexture = NULL;

  //Load image at specified path
  SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
  if( loadedSurface == NULL )
    {
      printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
  else
    {
      //Color key image
      SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

      //Create texture from surface pixels
      newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
      if( newTexture == NULL )
	{
	  printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	}
      else
	{
	  //Get image dimensions
	  mWidth = loadedSurface->w;
	  mHeight = loadedSurface->h;
	}

      //Get rid of old loaded surface
      SDL_FreeSurface( loadedSurface );
    }

  //Return success
  mTexture = newTexture;
  return mTexture != NULL;
}

void LTexture::free()
{
  //Free texture if it exists
  if( mTexture != NULL )
    {
      SDL_DestroyTexture( mTexture );
      mTexture = NULL;
      mWidth = 0;
      mHeight = 0;
    }
}

void LTexture::render( int x, int y, SDL_Rect* clip )
{
  //Set rendering space and render to screen
  SDL_Rect renderQuad = { x, y, mWidth, mHeight };

  //Set clip rendering dimensions
  if( clip != NULL )
    {
      renderQuad.w = clip->w;
      renderQuad.h = clip->h;
    }

  //Render to screen
  SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

int LTexture::getWidth()
{
  return mWidth;
}

int LTexture::getHeight()
{
  return mHeight;
}

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;
}

void LButton::setPosition( int x, int y )
{
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::handleEvent( SDL_Event* e )
{
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < mPosition.x )
		{
			inside = false;
		}

		//Mouse is right of the button
		else if( x > mPosition.x + BUTTON_WIDTH )
		{
			inside = false;
		}

		//Mouse above the button
		else if( y < mPosition.y )
		{
			inside = false;
		}

		//Mouse below the button
		else if( y > mPosition.y + BUTTON_HEIGHT )
		{
			inside = false;
		}

		//MOUSE is inside button
		if(! inside )
		{

			switch( e->type )
			{
				case SDL_MOUSEBUTTONDOWN:
					//Clear screen
					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	                            	SDL_RenderClear( gRenderer );

					//Render top left sprite
	                                gTexture.render( x, y, &gANDGATE );
								                                                                      //Update screen
                                         SDL_RenderPresent( gRenderer );				

				break;


			}
		}
	}
}

bool init()
{
  //Initialization flag
  bool success = true;

  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
      printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
      success = false;
    }
  else
    {
      //Set texture filtering to linear
      if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
	{
	  printf( "Warning: Linear texture filtering not enabled!" );
	}

      //Create window
      gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
      if( gWindow == NULL )
	{
	  printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
	  success = false;
	}
      else
	{
	  //Create renderer for window
	  gRenderer = SDL_CreateRenderer( gWindow, -1, 0 );
	  if( gRenderer == NULL )
	    {
	      printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
	      success = false;
	    }
	  else
	    {
	      //Initialize renderer color
	      SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

	      //Initialize PNG loading
	      int imgFlags = IMG_INIT_PNG;
	      if( !( IMG_Init( imgFlags ) & imgFlags ) )
		{
		  printf( "SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
		  success = false;
		}
	    }
	}
    }

  return success;
}

bool loadMedia()
{
  //Loading success flag
  bool success = true;

  //Load sprite sheet texture
  if( !gTexture.loadFromFile( "and_gate.png" ) )
    {
      printf( "Failed to load sprite sheet texture!\n" );
      success = false;
    }
  else
    {
      //Set top left sprite
      gANDGATE.x =   0;
      gANDGATE.y =   0;
      gANDGATE.w = BUTTON_WIDTH;
      gANDGATE.h = BUTTON_HEIGHT;

      gButtons.setPosition(0,0);	

    }

  return success;
}

void close()
{
  //Free loaded images
  gTexture.free();

  //Destroy window
  SDL_DestroyRenderer( gRenderer );
  SDL_DestroyWindow( gWindow );
  gWindow = NULL;
  gRenderer = NULL;

  //Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}

int main( int argc, char* args[] )
{

	int x,y;
  //Start up SDL and create window
  if( !init() )
    {
      printf( "Failed to initialize!\n" );
    }
  else
    {
      //Load media
      if( !loadMedia() )
	{
	  printf( "Failed to load media!\n" );
	}
      else
	{
	  //Main loop flag
	  bool quit = false;

	  //Event handler
	  SDL_Event e;

	  //While application is running
	  while( !quit )
	    {
	      //Handle events on queue
	      while( SDL_PollEvent( &e ) != 0 )
		{
		  //User requests quit
		  if( e.type == SDL_QUIT )
		    {
		      quit = true;
		    }

			gButtons.handleEvent( &e );
		}


	    }
	}
    }

  //Free resources and close SDL
  close();

  return 0;
}
