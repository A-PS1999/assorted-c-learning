#include "forest-fire.h"
#include <unistd.h>
#include <string.h>
#include <math.h>

void setEmptyForest(Forest* forestSim);
bool shouldGrowTree(void);
bool shouldStrikeLightning(void);
bool shouldBurn(Forest* forestSim, int x, int y);
bool isInBounds(int checkX, int checkY);

bool isValidInput(int argc, char** argv) {
    if (argc != 2) {
        return false;
    }

    if (access(argv[1], F_OK) != 0) {
        return false;
    }

    return true;
}

bool readForestFile(Forest* forestSim, char* fileName) {
    FILE* file;

    file = fopen(fileName, "r");

    if (!file) {
        return false;
    }

    forestSim->height = BOARD_HEIGHT;
    forestSim->width = BOARD_WIDTH;

    char fileBuffer[FILE_BUFFER_LEN];

    int currRow = 0;

    while (fgets(fileBuffer, FILE_BUFFER_LEN, file) && currRow < forestSim->height) {
        
        for (int currCol=0; currCol < forestSim->width-1; currCol++) {
            forestSim->forest[currRow][currCol] = fileBuffer[currCol];
        }

        currRow++;
    }

    currRow = 0;

    for (; currRow < forestSim->height; currRow++) {
        forestSim->forest[currRow][forestSim->width-1] = '\0';
    }

    fclose(file);
    return true;
}

void setEmptyForest(Forest* forestSim) {

    memset(forestSim->forest, ' ', BOARD_HEIGHT*BOARD_WIDTH*sizeof(forestSim->forest[0][0]));

    for (int row=0; row < BOARD_HEIGHT; row++) {
        forestSim->forest[row][(BOARD_WIDTH-1)] = '\0';
    }
}

bool shouldGrowTree(void) {
    double growProbability = 1-(pow((1-(1/(double)G)), (double)G));
    double randomNum = ((double)rand()/RAND_MAX);

    return randomNum <= growProbability;
}

bool shouldStrikeLightning(void) {
    double strikeProbability = 1-(pow((1-(1/(double)L)), (double)L));
    double randomNum = ((double)rand()/RAND_MAX);

    return randomNum <= strikeProbability;
}

bool isInBounds(int checkX, int checkY) {
    if (checkX >= 0 && checkX < BOARD_WIDTH-1 && checkY >= 0 && checkY < BOARD_HEIGHT) {
        return true;
    }

    return false;
}

bool shouldBurn(Forest* forestSim, int x, int y) {
    
    bool res = false;

    for (int row = y-1; row <= y+1; row++) {
        for (int col=x-1; col <= x+1; col++) {
            if (isInBounds(col, row) && row != y && col != x) {
                if (forestSim->forest[row][col] == '*') {
                    return true;
                }
            }
        }
    }

    return res;
}

void updateSim(Forest* forestSim) {

    Forest nextForest;

    setEmptyForest(&nextForest);

    for (int row=0; row < forestSim->height; row++) {
        for (int col=0; col < forestSim->width-1; col++) {
            char currCellChar = forestSim->forest[row][col];

            switch (currCellChar) {
                case ' ':
                    if (shouldGrowTree()) {
                        nextForest.forest[row][col] = '@';
                    }
                    break;
                case '@':
                    if (shouldStrikeLightning()) {
                        nextForest.forest[row][col] = '*';
                    } else if (shouldBurn(forestSim, col, row)) {
                        nextForest.forest[row][col] = '*';
                    } else {
                        nextForest.forest[row][col] = '@';
                    }
                    break;
                case '*':
                    nextForest.forest[row][col] = ' ';
                    break;
                default:
                    assert(false);
                    break;
            }
        }
    }

    memcpy(&forestSim->forest, &nextForest.forest, sizeof(forestSim->forest));
}

void printSim(Forest* forestSim) {

    for (int row=0; row < forestSim->height; row++) {
        printf("%s\n", forestSim->forest[row]);
    }
    printf("----------------------------------------\n");
}
