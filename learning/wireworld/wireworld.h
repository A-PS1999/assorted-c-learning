#ifndef WIREWORLD_H
#define WIREWORLD_H

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define TOTAL_GENS 1000
#define BOARD_WIDTH 41
#define BOARD_HEIGHT 40

#define FILE_BUFFER_LINE_LEN 45

typedef struct Board {
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    int width;
    int height;
} Board;

extern Board wireBoard;

bool isValidInput(int argc, char** argv);
bool initBoard(Board* wireBoard, char* fileName);
void updateBoard(Board* wireBoard);
void printBoard(Board* wireBoard);

#endif