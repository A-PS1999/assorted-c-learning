#include "conways_game_106.h"

int main(int argc, char** argv) {
    if (!isValidInput(argc, argv)) {
        perror("Error - Inputs are invalid: ");
        return -1;
    }

    Board gameBoard;
    int numIterations = (int) strtol(argv[2], (char**)NULL, 10);
    int currIteration = 0;

    if (!initBoard(&gameBoard, argv[1])) {
        perror("Error - Failed to initialise game board: ");
        return -1;
    }

    while (currIteration < numIterations) {
        printBoard(&gameBoard);
        updateGameState(&gameBoard);
        currIteration++;
    }

    return 0;
}