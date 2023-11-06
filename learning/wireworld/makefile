# Use clang, but could be gcc
CC=gcc

# Our 'core' set of flags used for everything
BASEFLAGS= -g -Wall -Wextra -Wpedantic -std=c99 -Wvla -Wfloat-equal

# Optimise code, but allow no warnings during compilation
PRODFLAGS=$(BASEFLAGS) 
# Be super tough - fail to compile if *any* errors
# PRODFLAGS=$(BASEFLAGS) -O1 -Werror

all : wireworld wireworld_dbg

# Production Code - no warnings allowed, no sanitizer
wireworld : wireworld.c wireworld-funcs.c wireworld.h
	$(CC) wireworld.c wireworld-funcs.c -o wireworld $(PRODFLAGS)

# Development Code - sanitizer enabled
wireworld_dbg : wireworld.c wireworld-funcs.c wireworld.h
	$(CC) wireworld.c wireworld-funcs.c -o wireworld_dbg

all: wireworld wireworld_dbg

clean:
	rm -f wireworld wireworld_dbg