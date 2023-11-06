# Use clang, but could be gcc
CC=gcc

# Our 'core' set of flags used for everything
BASEFLAGS=-ggdb -Wall -Wextra -Werror -pedantic -std=c99
# return these baseflags: -Wall -Wextra -Wpedantic -std=c99 -Wvla -Wfloat-equal
# Optimise code, but allow no warnings during compilation
PRODFLAGS=$(BASEFLAGS) 
# Be super tough - fail to compile if *any* errors
# PRODFLAGS=$(BASEFLAGS) -O1 -Werror

# Not optimisation, add in Sanitizer code -> huge executable file but will tell you if an array goes out-of-bounds etc.
DBGFLAGS=$(BASEFLAGS) -g3 

all : word-ladder word-ladder_dbg

# Production Code - no warnings allowed, no sanitizer
word-ladder: word-ladder.c ladder-funcs.c stack.c
	$(CC) word-ladder.c ladder-funcs.c stack.c -o word-ladder $(PRODFLAGS)

# Development Code - sanitizer enabled
word-ladder_dbg: word-ladder.c ladder-funcs.c stack.c
	$(CC) word-ladder.c ladder-funcs.c stack.c -o word-ladder_dbg $(DBGFLAGS)

all: word-ladder word-ladder_dbg

clean:
	rm -f word-ladder word-ladder_dbg