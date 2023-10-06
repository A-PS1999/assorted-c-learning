#ifndef CONWAYS_106_H
#define CONWAYS_106_H

#define _POSIX_C_SOURCE 200112L

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// The board that gets displayed is 150 wide and 90 tall, but padding on width is for null char
#define BOARD_WIDTH 152
#define BOARD_HEIGHT 90

#define FILE_LINE_BUFFER_LEN 11

typedef struct Board {
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    int width;
    int height;
} Board;

extern Board gameBoard;

bool isValidInput(int argCount, char** argVals);
bool initBoard(Board* gameBoard, char* fileName);
void updateGameState(Board* gameBoard);
void printBoard(const Board* gameBoard);

#endif