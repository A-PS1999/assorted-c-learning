# Use clang, but could be gcc
CC=gcc

# Our 'core' set of flags used for everything
BASEFLAGS=-g -Wall -Werror -pedantic -std=c99
# return these baseflags: -Wall -Wextra -Wpedantic -std=c99 -Wvla -Wfloat-equal
# Optimise code, but allow no warnings during compilation
PRODFLAGS=$(BASEFLAGS) 
# Be super tough - fail to compile if *any* errors
# PRODFLAGS=$(BASEFLAGS) -O1 -Werror

# Not optimisation, add in Sanitizer code -> huge executable file but will tell you if an array goes out-of-bounds etc.
DBGFLAGS=$(BASEFLAGS) -g3 
LDLIBS= -lm

all : anagrams anagrams_dbg

# Production Code - no warnings allowed, no sanitizer
anagrams : anagrams.c anagram-funcs.c anagrams.h
	$(CC) anagrams.c anagram-funcs.c -o anagrams $(PRODFLAGS) $(LDLIBS)

# Development Code - sanitizer enabled
anagrams_dbg : anagrams.c anagram-funcs.c anagrams.h
	$(CC) anagrams.c anagram-funcs.c -o anagrams_dbg $(DBGFLAGS) $(LDLIBS)

all: anagrams anagrams_dbg

clean:
	rm -f anagrams anagrams_dbg