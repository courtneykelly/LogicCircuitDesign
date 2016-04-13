all: main

main: main.cpp
	g++ main.cpp -I/usr/local/include/SDL2 -D_THREAD_SAFE -L/usr/local/lib -lSDL2 -o SDLTest

clean:
	rm -f SDLTest