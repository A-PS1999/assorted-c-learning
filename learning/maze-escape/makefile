# Use clang, but could be gcc
CC=gcc

# Our 'core' set of flags used for everything
BASEFLAGS=-g -Wall -Wextra -Werror -pedantic -std=c99 -Wvla -Wfloat-equal
# return these baseflags: -Wall -Wextra -Wpedantic -std=c99 -Wvla -Wfloat-equal
# Optimise code, but allow no warnings during compilation
PRODFLAGS=$(BASEFLAGS) 
# Be super tough - fail to compile if *any* errors
# PRODFLAGS=$(BASEFLAGS) -O1 -Werror

# Not optimisation, add in Sanitizer code -> huge executable file but will tell you if an array goes out-of-bounds etc.
DBGFLAGS=$(BASEFLAGS) -g3

all : maze-escape maze-escape_dbg

# Production Code - no warnings allowed, no sanitizer
maze-escape: maze-escape.c maze-funcs.c
	$(CC) maze-escape.c maze-funcs.c -o maze-escape $(PRODFLAGS)

# Development Code - sanitizer enabled
maze-escape_dbg: maze-escape.c maze-funcs.c
	$(CC) maze-escape.c maze-funcs.c -o maze-escape_dbg $(DBGFLAGS)

all: maze-escape maze-escape_dbg

clean:
	rm -f maze-escape maze-escape_dbg