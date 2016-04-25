#OBJS specifies which files to compile as part of the project
OBJS = clip_render.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -L/usr/local/lib -lSDL2 -lSDL2_gfx -lSDL2_image -I/usr/local/include/SDL2 \
 -D_THREAD_SAFE 
#-lSDL2 -lSDL2_image 

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = clip

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

