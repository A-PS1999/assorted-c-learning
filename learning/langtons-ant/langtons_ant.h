#ifndef LANGTONS_ANT_H
#define LANGTONS_ANT_H

#include <stdbool.h>
#include <stdio.h>

#define NUM_ITERATIONS 40

#define BOARD_WIDTH 21
#define BOARD_HEIGHT 20

typedef Board {
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    int width;
    int height;
} Board;

typedef Ant {
    int posX;
    int posY;
    
} Ant;

extern Board simBoard;

void initBoard(Board* board);
void updateBoard(Board* board);
void printBoard(Board* board);

#endif
