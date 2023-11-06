# Use clang, but could be gcc
CC=gcc

# Our 'core' set of flags used for everything
BASEFLAGS=-g -Wall -Wextra -Wpedantic -std=c99 -Wvla -Wfloat-equal

# Optimise code, but allow no warnings during compilation
PRODFLAGS=$(BASEFLAGS) -O1
# Be super tough - fail to compile if *any* errors
# PRODFLAGS=$(BASEFLAGS) -O1 -Werror

# Not optimisation, add in Sanitizer code -> huge executable file but will tell you if an array goes out-of-bounds etc.
DBGFLAGS=$(BASEFLAGS) -g3 

all : anagram-list anagram-list-dbg

# Production Code - no warnings allowed, no sanitizer
anagram-list : anagram-list.c funcs.c anagram-list.h
	$(CC) anagram-list.c funcs.c -o anagram-list $(PRODFLAGS)

# Development Code - sanitizer enabled
anagram-list-dbg : anagram-list.c funcs.c anagram-list.h
	$(CC) anagram-list.c funcs.c -o anagram-list-dbg $(DBGFLAGS)

all: anagram-list anagram-list-dbg

clean:
	rm -f anagram-list anagram-list-dbg