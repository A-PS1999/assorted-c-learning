#ifndef LIFE_WARS_H
#define LIFE_WARS_H

#define _POSIX_C_SOURCE 200112L

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define MAX_INIT_ATTEMPTS 100

#define BOARD_WIDTH 152
#define BOARD_HEIGHT 90

#define FILE_BUFFER_LINE_LEN 15

#define TOTAL_GAMES 50
#define TOTAL_GENS 5000

typedef struct Board {
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    int width;
    int height;
    unsigned int playerACells;
    unsigned int playerBCells;
    char* playerAStarts;
    char* playerBStarts;
} Board;

typedef struct Vec2 {
    int x;
    int y;
} Vec2;

extern Board gameBoard;

bool isValidInput(int argCount, char** argVals);
bool setBoardStart(Board* gameBoard, char* aFile, char* bFile, bool* first);
void playGame(Board* gameBoard, int* aTotal, int* bTotal);
void printGameStats(int gameNum, Board* gameBoard, int aTotal, int bTotal);
void printWinner(int aTotal, int bTotal);

#endif