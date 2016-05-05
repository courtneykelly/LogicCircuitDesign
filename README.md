Logic Circuit Simulator -- User Manual
--------------------------------------
--------------------------------------

Additional Libraries Needed & Machine Info
------------------------------------------

We download several libraries to expand the functionality of our design. Installation is for Mac OS X, using the Homebrew package manager. They are listed in the following list: 
	
	Library: SDL
	Installation: $ brew install sdl
	
	Library: SDL2
	Installation: $ brew install sdl2
	Compiler CFlags: -I/usr/local/include/SDL2 -D_THREAD_SAFE
	Compiler Library Linking Flags: -L/usr/local/lib -lSDL2

	Library: SLD2_gfx
	Installation: $ brew install sdl2_gfx
	Compiler Library Linking Flags: -lSDL2_gfx
	
	Library: SDL_image
	Installation: $ brew install sdl_image
	
	Library: SDL2_image
	Installation: $ brew install sdl2_image
	Compiler Library Linking Flags: -lSDL2_image
	
	Library: SDL2_ttf
	Installation: $ brew install sdl2_ttf
	Compiler Library Linking Flags: -lSDL2_ttf
	        
We decided to switch from using the Notre Dame student machines (linux) to our own personal machines (Mac OS X Darwin) to save time throughout the project. Using personal machines, we eliminated having to ssh and use the terminal emulator xterm. This also enabled us to use different text editors to write our code including Sublime Text 2. In using our personal machines, all of the above libraries needed to be installed to run our program. We all have Mac OS X machines, so we simply used the “package manager” Homebrew to install all of these libraries.

Compilation Instructions
------------------------

Compiling can be tricky. Once you use Homebrew or the package manager of your choice to install the needed libraries, you need to find out where they are stored on your computer in order to compile our program. Since we are using SDL2, you need the path to the SDL2 include file (cflag). This is usually stored in /usr/local/include, and passed to the compiler with the -I (include flag) followed by the path as such: -I/usr/local/include/SDL2 -D_THREAD_SAFE. You then need to link the path to where all your local libraries are stored. This is usually: /usr/local/lib. Your local libraries folder should contain all the libraries you used Homebrew (or other package manager) to install. You need to link this path and the appropriate libraries with the -L (library linker flag) followed by all of the libraries you want to include when you compile. The command is as such: -L/usr/local/lib -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf. Once you combine these compiler commands with g++, your main.cpp, and your object flags, you should have a fully working compilation. Our final compiler command was: 

g++ main.cpp -w -L/usr/local/lib -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -I/usr/local/include/SDL2 -D_THREAD_SAFE  -o project

If this compilation doesn’t work and all the include files and libraries are linked correctly during compilation, the error is probably in your headers: 
        #include <SDL.h>
	#include "SDL2_gfxPrimitives.h"
	#include "SDL_image.h"
	#include "SDL_ttf.h"

Look for these files in your /usr/local directory. With Homebrew, they are installed in the /usr/local/Cellar directory. Once there, find the respective header file (.h) for that library and make sure it is named correctly in your header and linked correctly when compiled.

User Interaction Instructions
-----------------------------

When the simulator is run, the program will display a window with different buttons and smaller boxes.  The logic canvas, the larger box in the middle, has three input ports to the left of the box labeled ‘a’, ‘b’, and ‘c’ and one output port to the right labeled ‘z’.  This is where the circuit is to be drawn.  To add a gate to the logic canvas, the user will click on one of the gates in the box to the right of the canvas.  The user has the option of choosing an “And gate”, “Or gate”, or “Not gate”.  When one of these has been selected, the gate will appear on the logic canvas.  The user can then use the mouse to drag and drop the gate to the desired location within the logic canvas.  To connect the inputs to the gates, the user can use the mouse to click on a port and drag the mouse to another port.  A wire will appear and snap into place as long as it is connected appropriately.  If the user tries to connect the wire inappropriately, the wire will disappear as soon as the user releases the mouse button.  Once the user has connected the circuit to the output, the program will display the logic equation corresponding to the circuit directly above the logic canvas. The user can also change the value of the inputs by clicking on the input boxes.  If the user clicks on a 0, the value will change to a 1 and vis versa.   The output value will change corresponding to the input values and the circuit.  If the user wishes to create another circuit or to start over, they can click the clear button which will reset the program to the beginning state.

Known bugs
----------

We don’t have many known bugs, but they are listed as follows:

	1. The NOT gate out port has some troubles. Our other gates are detected 		according to their size, but the NOT gate is detected with a box around the 	triangle. So you can click outside the body of the NOT gate and it will still 	move the gate. This is inconsistent with our other two gates, where you can 	only click on the body.

	2. If you have a very large logic circuit, the equation corresponding to it 	will also be very large. If it is too large, instead of resizing the equation 	to fit the window, the equation will run off the screen and not display the 	whole thing.

Additional Info
---------------

There are no special equipment or libraries are required.

EOF