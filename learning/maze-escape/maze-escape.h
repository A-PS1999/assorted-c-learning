#ifndef MAZE_ESCAPE_H
#define MAZE_ESCAPE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZEBUFFER_LEN 10
#define NEIGHBOURARR_LEN 4

typedef struct Maze {
    char** maze;
    int width;
    int height;
} Maze;

typedef struct XYPos {
    int x;
    int y;
} XYPos;

bool isValidInput(int argc, char** argv, int* mazeWidth, int* mazeHeight);
Maze* initMaze(char* fileName, int width, int height);
void solveMaze(Maze* maze, bool* solved);
XYPos getStartPos(Maze* maze);
void recurseMaze(Maze* maze, int posX, int posY, bool* solved);
void recurseWalls(Maze* maze, int posX, int posY, char fillChar);
void floodFillWalls(Maze* maze, int startX, int startY);
void printMaze(Maze* maze);
void freeMaze(Maze* maze);
bool isInBounds(Maze* maze, int row, int col);
bool isUnvisitedSpace(Maze* maze, int row, int col);

#endif
