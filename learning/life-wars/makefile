# Use clang, but could be gcc
CC=gcc

# Our 'core' set of flags used for everything
BASEFLAGS= -g3 -Wall -Wextra -Wpedantic -std=c99 -Wvla -Wfloat-equal

# Optimise code, but allow no warnings during compilation
PRODFLAGS=$(BASEFLAGS) -O1 -Werror
# Be super tough - fail to compile if *any* errors
# PRODFLAGS=$(BASEFLAGS) -O1 -Werror

# Not optimisation, add in Sanitizer code -> huge executable file but will tell you if an array goes out-of-bounds etc.
#DBGFLAGS=$(BASEFLAGS) -fsanitize=address -fsanitize=undefined -g3 
LDLIBS= -lm

all : life_wars life_wars_dbg

# Production Code - no warnings allowed, no sanitizer
life_wars : life-wars.c life-wars-funcs.c life-wars.h
	$(CC) life-wars.c life-wars-funcs.c -o life_wars $(PRODFLAGS) $(LDLIBS)

# Development Code - sanitizer enabled
life_wars_dbg : life-wars.c life-wars-funcs.c life-wars.h
	$(CC) life-wars.c life-wars-funcs.c -o life_wars_dbg $(LDLIBS)

all: life_wars life_wars_dbg

clean:
	rm -f life_wars life_wars_dbg