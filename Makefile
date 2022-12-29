#OBJS specifies which files to compile as part of the project
OBJS = Source/main.c Source/C8.c Source/DisTim.c Source/Input.c

#CC specifies which compiler we're using
CC = gcc

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = chip8emu

OBJ_NAME_DEBUG = chip8emugdb

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

gdb : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -g $(LINKER_FLAGS) -o $(OBJ_NAME_DEBUG)
sdl_test : SDL_Test.c
	$(CC) SDL_Test.c $(COMPILER_FLAGS) -g $(LINKER_FLAGS) -o sdl_test