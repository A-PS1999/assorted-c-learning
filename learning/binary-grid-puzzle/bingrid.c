#include "bingrid.h"

typedef enum FillType { ROW, COL } FillType;

void attemptBoardFill(board* board);
bool countingFill(board* board, int currRow, int currCol, FillType fillType, char fillVal);
bool checkBoardSolved(const board* board);
char getCellContent(int i, int j, board* board);
bool tryPairsRule(int i, int j, board* board);
bool tryOxoRule(int i, int j, board* board);
bool tryCountingRule(board* board);

bool str2board(board* brd, char* str) {
    int strLen = strlen(str);
    int gridSize = sqrt(strLen);

    if (brd == NULL || strLen == 0 || (strLen % 2) != 0) {
        return false;
    }

    char* strPtr = str;

    for (int i=0; i < gridSize; i++) {
        for (int j=0; j < gridSize; j++) {
            brd->b2d[i][j] = *strPtr;
            strPtr++;
        }
    }

    brd->sz = gridSize;

    return true;
}

void board2str(char* str, board* brd) {
    if (brd->sz == 0) {
        strcpy(str, "");
        return;
    }

    int fullSize = (brd->sz * brd->sz)+1;

    char* currChar = calloc(fullSize, sizeof(*currChar));
    char* startPtr = currChar;

    for (int i=0; i < brd->sz; i++) {
        for (int j=0; j < brd->sz; j++) {
            *currChar = brd->b2d[i][j];
            currChar++;
        }
    }

    strcpy(str, startPtr);
    free(startPtr);
}

bool solve_board(board* brd) {
    attemptBoardFill(brd);
    return checkBoardSolved(brd);
}

void test(void) {
}

void attemptBoardFill(board* board) {

    int size = board->sz;
    bool pairsFlag = false;
    bool oxoFlag = false;
    bool countingFlag = false;

    do {
        pairsFlag = false;
        oxoFlag = false;
        countingFlag = false;

        for (int i=0; i < size; i++) {
            for (int j=0; j < size; j++) {
                if (tryPairsRule(i, j, board)) {
                    pairsFlag = true;
                }
                if (tryOxoRule(i, j, board)) {
                    oxoFlag = true;
                }
            }
        }

        if (tryCountingRule(board)) {
            countingFlag = true;
        }

    } while (pairsFlag != false || oxoFlag != false || countingFlag != false);
}

bool tryPairsRule(int i, int j, board* board) {
    char currCell = board->b2d[i][j];
    char charToAdd = (currCell == '1') ? '0' : '1';
    bool ruleApplied = false;

    switch (currCell) {
        case '.':
            break;
        case '0':
        case '1':
            if ((getCellContent(i, j+1, board) == currCell) && (getCellContent(i, j-1, board) == '.')) {
                board->b2d[i][j-1] = charToAdd;
                ruleApplied = true;
            }
            if ((getCellContent(i-1, j, board) == currCell) && (getCellContent(i+1, j, board) == '.')) {
                board->b2d[i+1][j] = charToAdd;
                ruleApplied = true;
            }
            if ((getCellContent(i, j-1, board) == currCell) && (getCellContent(i, j+1, board) == '.')) {
                board->b2d[i][j+1] = charToAdd;
                ruleApplied = true;
            }
            if ((getCellContent(i+1, j, board) == currCell) && (getCellContent(i-1, j, board) == '.')) {
                board->b2d[i-1][j] = charToAdd;
                ruleApplied = true;
            }
            break;
        default:
            assert(false);
            break;
    }

    return ruleApplied;
}

bool tryOxoRule(int i, int j, board* board) {
    if (board->b2d[i][j] != '.') return false;

    bool ruleApplied = false;

    if ((getCellContent(i, j-1, board) == '1') && (getCellContent(i, j+1, board) == '1')) {
        board->b2d[i][j] = '0';
        ruleApplied = true;
    }
    if ((getCellContent(i-1, j, board) == '1') && (getCellContent(i+1, j, board) == '1')) {
        board->b2d[i][j] = '0';
        ruleApplied = true;
    }
    if ((getCellContent(i, j-1, board) == '0') && (getCellContent(i, j+1, board) == '0')) {
        board->b2d[i][j] = '1';
        ruleApplied = true;
    }
    if ((getCellContent(i-1, j, board) == '0') && (getCellContent(i+1, j, board) == '0')) {
        board->b2d[i][j] = '1';
        ruleApplied = true;
    }

    return ruleApplied;
}

bool countingFill(board* board, int currRow, int currCol, FillType fillType, char fillVal) {
    int size = board->sz;
    bool appliedRule = false;

    switch (fillType) {
        case ROW:

            for (int col=0; col < size; col++) {
                if (board->b2d[currRow][col] == '.') {
                    board->b2d[currRow][col] = fillVal;
                    appliedRule = true;
                }
            }

            break;
        case COL:

            for (int row=0; row < size; row++) {
                if (board->b2d[row][currCol] == '.') {
                    board->b2d[row][currCol] = fillVal;
                    appliedRule = true;
                }
            }

            break;
        default:
            assert(false);
            break;
    }

    return appliedRule;
}

bool tryCountingRule(board* board) {
    int size = board->sz;
    int numTarget = size / 2;
    bool ruleApplied = false;

    int numZeroes = 0;
    int numOnes = 0;

    int currRow = 0;
    int currCol = 0;

    while (currCol < size ) {

        for (int row = 0; row < size; row++) {
            if (board->b2d[row][currCol] == '0') numZeroes++;
            if (board->b2d[row][currCol] == '1') numOnes++;

            if (((numZeroes == numTarget) || (numOnes == numTarget))) {
                char toFillWith = (numZeroes == numTarget) ? '1' : '0';
                ruleApplied = countingFill(board, row, currCol, COL, toFillWith);
            }
        }

        numZeroes = 0;
        numOnes = 0;
        currCol++;
    }

    while (currRow < size) {

        for (int col=0; col < size; col++) {
            if (board->b2d[currRow][col] == '0') numZeroes++;
            if (board->b2d[currRow][col] == '1') numOnes++;

            if (((numZeroes == numTarget) || (numOnes == numTarget))) {
                char toFillWith = (numZeroes == numTarget) ? '1' : '0';
                ruleApplied = countingFill(board, currRow, col, ROW, toFillWith);
            }
        }

        numZeroes = 0;
        numOnes = 0;
        currRow++;
    }

    return ruleApplied;
}

bool checkBoardSolved(const board* board) {
    int size = board->sz;

    for (int i=0; i < size; i++) {
        for (int j=0; j < size; j++) {
            if (board->b2d[i][j] == '.') {
                return false;
            }
        }
    }

    return true;
}

char getCellContent(int i, int j, board* board) {
    int size = board->sz;

    if (i >= 0 && i < size && j >= 0 && j < size) {
        return board->b2d[i][j];
    } else {
        return '\0';
    }
}