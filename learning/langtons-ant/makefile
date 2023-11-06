# Use clang, but could be gcc
CC=clang

# Our 'core' set of flags used for everything
BASEFLAGS=-g -Wall -Wextra -Wfloat-equal -Wvla -pedantic -std=c99
# return these baseflags: -Wall -Wextra -Wpedantic -std=c99 -Wvla -Wfloat-equal
# Optimise code, but allow no warnings during compilation
PRODFLAGS=$(BASEFLAGS) -O1
# Be super tough - fail to compile if *any* errors
# PRODFLAGS=$(BASEFLAGS) -O1 -Werror

# Not optimisation, add in Sanitizer code -> huge executable file but will tell you if an array goes out-of-bounds etc.
DBGFLAGS=$(BASEFLAGS) -fsanitize=address -fsanitize=undefined -g3 
LDLIBS= -lm

all : langtons_ant langtons_ant_dbg

# Production Code - no warnings allowed, no sanitizer
langtons_ant : langtons_ant.c ant_funcs.c langtons_ant.h
	$(CC) langtons_ant.c ant_funcs.c -o langtons_ant $(PRODFLAGS) $(LDLIBS)

# Development Code - sanitizer enabled
langtons_ant_dbg : langtons_ant.c ant_funcs.c langtons_ant.h
	$(CC) langtons_ant.c ant_funcs.c -o langtons_ant_dbg $(DBGFLAGS) $(LDLIBS)

all: langtons_ant langtons_ant_dbg

clean:
	rm -f langtons_ant langtons_ant_dbg