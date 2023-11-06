#ifndef FOREST_FIRE_H
#define FOREST_FIRE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#define TOTAL_GENS 1000
#define BOARD_WIDTH 81
#define BOARD_HEIGHT 30

#define FILE_BUFFER_LEN 85

#define G 250
#define L (G * 10)

typedef struct Forest {
    char forest[BOARD_HEIGHT][BOARD_WIDTH];
    int width;
    int height;
} Forest;

extern Forest forestSim;

bool isValidInput(int argc, char** argv);
bool readForestFile(Forest* forestSim, char* fileName);
void updateSim(Forest* forestSim);
void printSim(Forest* forestSim);

#endif
