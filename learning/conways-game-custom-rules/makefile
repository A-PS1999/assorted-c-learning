# Use clang, but could be gcc
CC=gcc

# Our 'core' set of flags used for everything
BASEFLAGS= -g -Wall -Wextra -Wpedantic -std=c99 -Wvla -Wfloat-equal

# Optimise code, but allow no warnings during compilation
PRODFLAGS=$(BASEFLAGS) 
# Be super tough - fail to compile if *any* errors
# PRODFLAGS=$(BASEFLAGS) -O1 -Werror

# Not optimisation, add in Sanitizer code -> huge executable file but will tell you if an array goes out-of-bounds etc.
#DBGFLAGS=$(BASEFLAGS) -fsanitize=address -fsanitize=undefined -g3 
LDLIBS= -lm

all : conways_game conways_game_dbg

# Production Code - no warnings allowed, no sanitizer
conways_game : conways-game-custom.c gamefuncs.c conways_game_custom.h
	$(CC) conways-game-custom.c gamefuncs.c -o conways_game $(PRODFLAGS) $(LDLIBS)

# Development Code - sanitizer enabled
conways_game_dbg : conways-game-custom.c gamefuncs.c conways_game_custom.h
	$(CC) conways-game-custom.c gamefuncs.c -o conways_game_dbg $(LDLIBS)

all: conways_game conways_game_dbg

clean:
	rm -f conways_game conways_game_dbg