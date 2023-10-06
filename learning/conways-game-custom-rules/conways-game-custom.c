#include "conways_game_custom.h"

int main(int argc, char** argv) {
    if (!isValidInput(argc, argv)) {
        perror("Error - Invalid inputs provided");
        return -1;
    }

    Board gameBoard;

    if (!initBoard(&gameBoard, argv[2], argv[1])) {
        perror("Error - Failed to initialise board");
        return -1;
    }

    for (int currGeneration = 0; currGeneration < MAX_GENERATIONS; currGeneration++) {
        printBoard(&gameBoard);
        updateGameState(&gameBoard);
    }

    return 0;
}