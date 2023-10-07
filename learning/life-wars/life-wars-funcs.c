#include "life-wars.h"
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int getNumFileLines(char* fileName);
void setEmptyBoard(Board* gameBoard);
void setInitialCells(Board* gameBoard, bool* flag, char* aFile, char* bFile, bool* first);
void readLifFile(Board* gameBoard, char* fileName, bool* flag, char player);
void readStartsBuffer(Board* gameBoard, Vec2 origin, bool* flag, char player);
bool placeInitialCell(Board* gameBoard, Vec2 origin, int x, int y, char player);
void updateCellStatus(Board* nextBoard, Board* currBoard, int x, int y);
int getNeighbourInfo(Board* currBoard, int currX, int currY, char* majority);
int checkNeighbour(Board* currBoard, int checkX, int checkY, int* aCount, int* bCount);

bool isValidInput(int argCount, char** argVals) {
    if (argCount != 3) return false;

    if ((access(argVals[1], F_OK) != 0) || (access(argVals[2], F_OK) != 0)) {
        return false;
    }

    int playerALines = getNumFileLines(argVals[1]);
    int playerBLines = getNumFileLines(argVals[2]);

    if ((playerALines > 100 || playerALines <= 1) || (playerBLines > 100 || playerBLines <= 1)) {
        return false;
    }

    return true;
}

void playGame(Board* gameBoard, int* aTotal, int* bTotal) {

    Board nextBoard;

    int currIteration = 0;

    while (currIteration < TOTAL_GENS) {
        setEmptyBoard(&nextBoard);

        for (int y=0; y < gameBoard->height; y++) {
            for (int x=0; x < gameBoard->width-1; x++) {
                updateCellStatus(&nextBoard, gameBoard, x, y);
            }
        }

        memcpy(&gameBoard->board, &nextBoard.board, sizeof(gameBoard->board));
        currIteration++;
    }

    (*aTotal) += gameBoard->playerACells;
    (*bTotal) += gameBoard->playerBCells;
}

void updateCellStatus(Board* nextBoard, Board* currBoard, int x, int y) {
    char currCellChar = currBoard->board[y][x];
    char majorityNeighbour = ' ';
    int numLivingNeighbours = getNeighbourInfo(currBoard, x, y, &majorityNeighbour);

    switch (currCellChar) {
        case ' ':
            if (numLivingNeighbours == 3) {
                if (majorityNeighbour == '#') {
                    nextBoard->board[y][x] = '#';
                    currBoard->playerACells++;
                } else if (majorityNeighbour == '@') {
                    nextBoard->board[y][x] = '@';
                    currBoard->playerBCells++;
                }
            }
            break;
        case '#':
        case '@':
            if (numLivingNeighbours == 2 || numLivingNeighbours == 3) {
                nextBoard->board[y][x] = currCellChar;
            } else {
                nextBoard->board[y][x] = ' ';

                if (currCellChar == '#') {
                    currBoard->playerACells--;
                } else {
                    currBoard->playerBCells--;
                }
            }
            break;
        default:
            assert(false);
            break;
    }
}

int checkNeighbour(Board* currBoard, int checkX, int checkY, int* aCount, int* bCount) {
    char neighbour = currBoard->board[checkY][checkX];

    if (neighbour == '#') {
        (*aCount)++;
        return 1;
    } else if (neighbour == '@') {
        (*bCount)++;
        return 1;
    }

    return 0;
}

int getNeighbourInfo(Board* currBoard, int currX, int currY, char* majority) {
    int res = 0;
    int aCount = 0;
    int bCount = 0;

    res += checkNeighbour(currBoard, (currX-1)%(currBoard->width-1), currY, &aCount, &bCount);
    res += checkNeighbour(currBoard, (currX+1)%(currBoard->width-1), currY, &aCount, &bCount);
    res += checkNeighbour(currBoard, currX, (currY-1)%(currBoard->height), &aCount, &bCount);
    res += checkNeighbour(currBoard, currX, (currY+1)%(currBoard->height), &aCount, &bCount);
    res += checkNeighbour(currBoard, (currX+1)%(currBoard->width-1), (currY+1)%(currBoard->height), &aCount, &bCount);
    res += checkNeighbour(currBoard, (currX-1)%(currBoard->width-1), (currY-1)%(currBoard->height), &aCount, &bCount);
    res += checkNeighbour(currBoard, (currX+1)%(currBoard->width-1), (currY-1)%(currBoard->height), &aCount, &bCount);
    res += checkNeighbour(currBoard, (currX-1)%(currBoard->width-1), (currY+1)%(currBoard->height), &aCount, &bCount);

    if (aCount > 0 || bCount > 0) {
        if (aCount > bCount) {
            *majority = '#';
        } else {
            *majority = '@';
        }
    } else {
        *majority = ' ';
    }

    return res;
}

int getNumFileLines(char* fileName) {

    FILE* file;

    file = fopen(fileName, "r");

    if (!file) {
        perror("Error - Failed to open file");
        assert(false);
    }

    fseek(file, 0, SEEK_END);
    size_t fileLen = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* fileBuffer = malloc(fileLen + 1);
    if (!fileBuffer) {
        perror("Error - Failed to allocate memory for file buffer");
        assert(false);
    }

    fread(fileBuffer, fileLen, 1, file);
    fclose(file);

    fileBuffer[fileLen] = '\0';

    int numLines = 0;

    while ((*fileBuffer) != '\0') {
        if ((*fileBuffer) == '\n') {
            numLines++;
        }

        fileBuffer++;
    }

    free(fileBuffer);

    return numLines;
}

void setEmptyBoard(Board* gameBoard) {
    gameBoard->width = BOARD_WIDTH;
    gameBoard->height = BOARD_HEIGHT;

    memset(gameBoard->board, ' ', BOARD_HEIGHT*BOARD_WIDTH*sizeof(gameBoard->board[0][0]));

    for (int row = 0; row < gameBoard->height; row++) {
        gameBoard->board[row][(gameBoard->width)-1] = '\0';
    }

    gameBoard->playerACells = 0;
    gameBoard->playerBCells = 0;
}

bool setBoardStart(Board* gameBoard, char* aFile, char* bFile, bool* firstInit) {

    int initAttempts = 0;
    bool initialCellsDistributed = true;

    do {
        setEmptyBoard(gameBoard);
        setInitialCells(gameBoard, &initialCellsDistributed, aFile, bFile, firstInit);
        initAttempts++;
    } while (!initialCellsDistributed && initAttempts < MAX_INIT_ATTEMPTS);

    if (initAttempts > MAX_INIT_ATTEMPTS) {
        return false;
    }

    return true;
}

void setInitialCells(Board* gameBoard, bool* flag, char* aFile, char* bFile, bool* first) {

    Vec2 aOrigin;
    Vec2 bOrigin;

    aOrigin.x = (rand() % ((gameBoard->width-2) - 0 + 1)) + 0;
    aOrigin.y = (rand() % ((gameBoard->height-1) - 0 + 1)) + 0;

    bOrigin.x = (rand() % ((gameBoard->width-2) - 0 + 1)) + 0;
    bOrigin.y = (rand() % ((gameBoard->height-1) - 0 + 1)) + 0;

    if (first) {
        readLifFile(gameBoard, aFile, flag, 'A');
        readLifFile(gameBoard, bFile, flag, 'B');
        (*first) = false;
    }

    readStartsBuffer(gameBoard, aOrigin, flag, 'A');
    readStartsBuffer(gameBoard, bOrigin, flag, 'B');
}

void readStartsBuffer(Board* gameBoard, Vec2 origin, bool* flag, char player) {
    
    char* copy;
    char* str;
    char* temp;

    int xVal;
    int yVal;
    
    switch (player) {
        case 'A':
            copy = calloc(strlen(gameBoard->playerAStarts)+1, sizeof(*gameBoard->playerAStarts));
            strcpy(copy, gameBoard->playerAStarts);

            str = strtok_r(copy, "\n", &temp);

            do {
                if (*str == '#') continue;

                sscanf(str, "%d %d", &xVal, &yVal);
                if (!placeInitialCell(gameBoard, origin, xVal, yVal, player)) {
                    (*flag) = false;
                    break;
                }
            } while ((str = strtok_r(NULL, "\n", &temp)) != NULL);

            break;
        case 'B':
            copy = calloc(strlen(gameBoard->playerBStarts)+1, sizeof(*gameBoard->playerBStarts));
            strcpy(copy, gameBoard->playerBStarts);

            str = strtok_r(copy, "\n", &temp);

            do {
                if (*str == '#') continue;

                sscanf(str, "%d %d", &xVal, &yVal);
                if (!placeInitialCell(gameBoard, origin, xVal, yVal, player)) {
                    (*flag) = false;
                    break;
                }
            } while ((str = strtok_r(NULL, "\n", &temp)) != NULL);
            
            break;
        default:
            assert(false);
            break;
    }

    free(copy);
}

bool placeInitialCell(Board* gameBoard, Vec2 origin, int x, int y, char player) {
    int newCellX = (origin.x + x) % (gameBoard->width-2);
    int newCellY = (origin.y + y) % gameBoard->height;

    char valAtNewCell = gameBoard->board[newCellY][newCellX];

    if (valAtNewCell == '#' || valAtNewCell == '@' || valAtNewCell == '\0') {
        return false;
    } else {
        gameBoard->board[newCellY][newCellX] = (player == 'A') ? '#' : '@';

        if (player == 'A') {
            gameBoard->playerACells += 1;
        } else {
            gameBoard->playerBCells += 1;
        }
        return true;
    }
}

void readLifFile(Board* gameBoard, char* fileName, bool* flag, char player) {

    FILE* file;

    file = fopen(fileName, "r");

    if (!file) {
        (*flag) = false;
        return;
    }

    fseek(file, 0, SEEK_END);
    size_t fileLen = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* fileBuffer = calloc(fileLen+1, sizeof(*fileBuffer));
    if (!fileBuffer) {
        perror("Error - Failed to allocate memory for file buffer");
        assert(false);
    }

    fread(fileBuffer, fileLen, 1, file);
    fclose(file);

    if (player == 'A') {
        gameBoard->playerAStarts = calloc(fileLen+2, sizeof(*gameBoard->playerAStarts));
        strcpy(gameBoard->playerAStarts, fileBuffer);
    } else {
        gameBoard->playerBStarts = calloc(fileLen+2, sizeof(*gameBoard->playerBStarts));
        strcpy(gameBoard->playerBStarts, fileBuffer);
    }

    free(fileBuffer);
}

void printGameStats(int gameNum, Board* gameBoard, int aTotal, int bTotal) {
    const char* A = "Player 1";
    const char* B = "Player 2";
    const char* D = "Draw";

    unsigned int aCells = gameBoard->playerACells;
    unsigned int bCells = gameBoard->playerBCells;

    if (aCells > bCells) {
        printf("%d %u %u %s\n", gameNum, aTotal, bTotal, A);
    } else if (bCells > aCells) {
        printf("%d %u %u %s\n", gameNum, aTotal, bTotal, B);
    } else {
        printf("%d %u %u %s\n", gameNum, aTotal, bTotal, D);
    }
}

void printWinner(int aTotal, int bTotal) {
    if (aTotal == bTotal) {
        printf("It's a draw! Somehow both players finished with exactly %d cells.\n", aTotal);
    } else if (aTotal > bTotal) {
        printf("Congratulations player 1! You win! You finished with %d cells, compared to %d for player 2.\n", aTotal, bTotal);
    } else {
        printf("Congratulations player 2! You win! You finished with %d cells, compared to %d for player 1.\n", bTotal, aTotal);
    }
}