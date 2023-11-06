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

all : forest_fire forest_fire_dbg

# Production Code - no warnings allowed, no sanitizer
forest_fire : forest-fire.c funcs.c forest-fire.h
	$(CC) forest-fire.c funcs.c -o forest_fire $(PRODFLAGS) $(LDLIBS)

# Development Code - sanitizer enabled
forest_fire_dbg : forest-fire.c funcs.c forest-fire.h
	$(CC) forest-fire.c funcs.c -o forest_fire_dbg $(DBGFLAGS) $(LDLIBS)

all: forest_fire forest_fire_dbg

clean:
	rm -f forest_fire forest_fire_dbg