#include "conways_game_106.h"
#include <ctype.h>

void setEmptyBoard(Board* gameBoard);
void fillInitialLiveCells(Board* gameBoard, int x, int y);
void changeBoardCellStatus(Board* nextBoard, Board* currBoard, int cellX, int cellY);
int getNumLiveNeighbours(Board* currBoard, int currX, int currY);
int checkNeighbour(Board* currBoard, int checkX, int checkY);

bool isValidInput(int argCount, char** argVals) {
    if (argCount != 3) return false;

    int iterations = (int) strtol(argVals[2], (char**)NULL, 10);

    if (iterations < 0) return false;

    return true;
}

void setEmptyBoard(Board* gameBoard) {
    gameBoard->width = BOARD_WIDTH;
    gameBoard->height = BOARD_HEIGHT;

    memset(gameBoard->board, ' ', BOARD_HEIGHT*BOARD_WIDTH*sizeof(gameBoard->board[0][0]));

    for (int row = 0; row < gameBoard->height; row++) {
        gameBoard->board[row][(gameBoard->width)-1] = '\0';
    }
}

bool initBoard(Board* gameBoard, char* fileName) {

    FILE* file;

    file = fopen(fileName, "r");

    if (!file) return false;

    setEmptyBoard(gameBoard);

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

    return true;
}

void fillInitialLiveCells(Board* gameBoard, int x, int y) {
    int middleCellX = (gameBoard->width-2) / 2;
    int middleCellY = (gameBoard->height) / 2;

    int liveCellX = middleCellX + x;
    int liveCellY = middleCellY + y;

    gameBoard->board[liveCellY][liveCellX] = '#';
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

void changeBoardCellStatus(Board* nextBoard, Board* currBoard, int cellX, int cellY) {
    char currCellChar = currBoard->board[cellY][cellX];
    int numLivingNeighbours = getNumLiveNeighbours(currBoard, cellX, cellY);

    switch (currCellChar) {
        case ' ':
            if (numLivingNeighbours == 3) {
                nextBoard->board[cellY][cellX] = '#';
            }
            break;
        case '#':
            if (numLivingNeighbours < 2 || numLivingNeighbours > 3) {
                nextBoard->board[cellY][cellX] = ' ';
            } else {
                nextBoard->board[cellY][cellX] = '#';
            }
            break;
        default:
            assert(false);
            break;
    }
}

void updateGameState(Board* gameBoard) {

    Board nextBoard;

    setEmptyBoard(&nextBoard);

    for (int y=0; y < gameBoard->height; y++) {
        for (int x=0; x < gameBoard->width-1; x++) {
            changeBoardCellStatus(&nextBoard, gameBoard, x, y);
        }
    }

    memcpy(&gameBoard->board, &nextBoard.board, sizeof(gameBoard->board));
}

void printBoard(const Board* gameBoard) {

    for (int i=0; i < gameBoard->height; i++) {
        printf("%s\n", gameBoard->board[i]);
    }

}