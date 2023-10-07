#include "conways_game_custom.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <regex.h>
#include <unistd.h>

void setRuleStr(Board* gameBoard, char* ruleStr);
void setEmptyBoard(Board* gameBoard, bool resetRules);
int checkNeighbour(Board* currBoard, int checkX, int checkY);
int getNumLiveNeighbours(Board* currBoard, int currX, int currY);
void fillInitialLiveCells(Board* gameBoard, int x, int y);
void changeBoardCellStatus(Board* nextBoard, Board* currBoard, int cellX, int cellY);
bool applyRules(Board* currBoard, char cellType, int neighbourNum);

bool isValidInput(int argCount, char** argVals) {
    if (argCount != 3) return false;

    regex_t rulesRegex;
    int regCompRes;

    regCompRes = regcomp(&rulesRegex, "B[0-8]+/S[0-8]+", REG_EXTENDED);

    if (regCompRes != 0) {
        return false;
    }

    int validStr = regexec(&rulesRegex, argVals[1], 0, NULL, 0);

    if (validStr == REG_NOMATCH) {
        return false;
    }

    if (access(argVals[2], F_OK) != 0) {
        return false;
    }

    return true;
}

bool initBoard(Board* gameBoard, char* fileName, char* ruleStr) {
    FILE* file;

    file = fopen(fileName, "r");

    if (!file) return false;

    setEmptyBoard(gameBoard, true);

    char fileBuffer[FILE_LINE_BUFFER_LEN];

    char* strPtr;
    char* xStr;
    char* yStr;

    while (true) {
        if (fgets(fileBuffer, FILE_LINE_BUFFER_LEN, file) == NULL) {
            break;
        };

        if ((!isdigit((unsigned char)fileBuffer[0])) && fileBuffer[0] != '-') continue;

        xStr = strtok_r(fileBuffer, " ", &strPtr);
        yStr = strtok_r(NULL, " ", &strPtr);
        fillInitialLiveCells(gameBoard, (int)strtol(xStr, (char**)NULL, 10), (int)strtol(yStr, (char**)NULL, 10));
    }

    setRuleStr(gameBoard, ruleStr);
    fclose(file);
    return true;
}

void setRuleStr(Board* gameBoard, char* ruleStr) {

    char* strPtr;
    char* birthStr;
    char* surviveStr;

    birthStr = strtok_r(ruleStr, "/", &strPtr);
    surviveStr = strtok_r(NULL, "/", &strPtr);

    int birthArrIdx = 0;

    while (*birthStr != '\0' && birthArrIdx < RULE_ARR_LEN) {
        if (isdigit((unsigned char)*birthStr)) {
            gameBoard->birthRules[birthArrIdx] = *birthStr - '0';
            birthArrIdx++;
        }

        birthStr++;
    }

    int surviveArrIdx = 0;

    while (*surviveStr != '\0' && surviveArrIdx < RULE_ARR_LEN) {
        if (isdigit((unsigned char)*surviveStr)) {
            gameBoard->survivalRules[surviveArrIdx] = *surviveStr - '0';
            surviveArrIdx++;
        }

        surviveStr++;
    }
}

void fillInitialLiveCells(Board* gameBoard, int x, int y) {
    int middleCellX = (gameBoard->width-2) / 2;
    int middleCellY = (gameBoard->height) / 2;

    int liveCellX = middleCellX + x;
    int liveCellY = middleCellY + y;

    gameBoard->board[liveCellY][liveCellX] = '#';
}

void setEmptyBoard(Board* gameBoard, bool resetRules) {
    gameBoard->width = BOARD_WIDTH;
    gameBoard->height = BOARD_HEIGHT;

    memset(gameBoard->board, ' ', BOARD_HEIGHT*BOARD_WIDTH*sizeof(gameBoard->board[0][0]));

    if (resetRules) {
        memset(gameBoard->birthRules, -1, RULE_ARR_LEN*sizeof(gameBoard->birthRules[0]));
        memset(gameBoard->survivalRules, -1, RULE_ARR_LEN*sizeof(gameBoard->survivalRules[0]));
    }

    for (int row = 0; row < gameBoard->height; row++) {
        gameBoard->board[row][(gameBoard->width)-1] = '\0';
    }
}

void updateGameState(Board* gameBoard) {
    Board nextBoard;

    setEmptyBoard(&nextBoard, false);

    for (int y=0; y < gameBoard->height; y++) {
        for (int x=0; x < gameBoard->width-1; x++) {
            changeBoardCellStatus(&nextBoard, gameBoard, x, y);
        }
    }

    memcpy(&gameBoard->board, &nextBoard.board, sizeof(gameBoard->board));
}

void changeBoardCellStatus(Board* nextBoard, Board* currBoard, int cellX, int cellY) {
    char currCellChar = currBoard->board[cellY][cellX];
    int numLivingNeighbours = getNumLiveNeighbours(currBoard, cellX, cellY);

    switch (currCellChar) {
        case ' ':
            if (applyRules(currBoard, currCellChar, numLivingNeighbours)) {
                nextBoard->board[cellY][cellX] = '#';
            }
            break;
        case '#':
            if (applyRules(currBoard, currCellChar, numLivingNeighbours)) {
                nextBoard->board[cellY][cellX] = '#';
            } else {
                nextBoard->board[cellY][cellX] = ' ';
            }
            break;
        default:
            assert(false);
            break;
    }
}

bool applyRules(Board* currBoard, char cellType, int neighbourNum) {

    switch (cellType) {
        case ' ':
            for (int i=0; i < RULE_ARR_LEN; i++) {
                if (currBoard->birthRules[i] == neighbourNum) {
                    return true;
                }
            }
            break;
        case '#':
            for (int j=0; j < RULE_ARR_LEN; j++) {
                if (currBoard->survivalRules[j] == neighbourNum) {
                    return true;
                } else {
                    return false;
                }
            }
            break;
        default:
            assert(false);
            break;
    }

    return false;
}

int checkNeighbour(Board* currBoard, int checkX, int checkY) {
    if (checkX >= 0 && checkX < currBoard->width-1 && checkY >= 0 && checkY < currBoard->height) {
        return currBoard->board[checkY][checkX] == '#' ? 1 : 0;
    }

    return 0;
}

int getNumLiveNeighbours(Board* currBoard, int currX, int currY) {
    int res = 0;

    res += checkNeighbour(currBoard, currX-1, currY);
    res += checkNeighbour(currBoard, currX+1, currY);
    res += checkNeighbour(currBoard, currX, currY-1);
    res += checkNeighbour(currBoard, currX, currY+1);
    res += checkNeighbour(currBoard, currX+1, currY+1);
    res += checkNeighbour(currBoard, currX-1, currY-1);
    res += checkNeighbour(currBoard, currX+1, currY-1);
    res += checkNeighbour(currBoard, currX-1, currY+1);

    return res;
}

void printBoard(const Board* gameBoard) {

    for (int i=0; i < gameBoard->height; i++) {
        printf("%s\n", gameBoard->board[i]);
    }

}