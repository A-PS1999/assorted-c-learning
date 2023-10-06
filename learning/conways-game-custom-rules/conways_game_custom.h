#ifndef CONWAYS_GAME_CUSTOM_H
#define CONWAYS_GAME_CUSTOM_H

#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define MAX_GENERATIONS 10
#define BOARD_WIDTH 152
#define BOARD_HEIGHT 90

#define RULE_ARR_LEN 9
#define FILE_LINE_BUFFER_LEN 15

typedef struct Board {
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    int width;
    int height;
    int birthRules[RULE_ARR_LEN];
    int survivalRules[RULE_ARR_LEN];
} Board;

extern Board gameBoard;

bool isValidInput(int argCount, char** argVals);
bool initBoard(Board* gameBoard, char* fileName, char* ruleStr);
void printBoard(const Board* gameBoard);
void updateGameState(Board* gameBoard);

#endif