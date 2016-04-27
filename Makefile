OBJS = main.cpp
CC = g++
COMPILER_FLAGS = -w
LINKER_FLAGS = -L/usr/local/lib -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -I/usr/local/include/SDL2 \
 -D_THREAD_SAFE 
OBJ_NAME = project


all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

