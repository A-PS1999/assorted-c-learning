#include "wireworld.h"

int main(int argc, char** argv) {
    if (!isValidInput(argc, argv)) {
        perror("Error - Invalid inputs provided");
        return -1;
    }

    Board wireBoard;

    if (!initBoard(&wireBoard, argv[1])) {
        perror("Error - Failed to initialise board");
        return -1;
    }

    for (int i=0; i < TOTAL_GENS; i++) {
        printBoard(&wireBoard);
        updateBoard(&wireBoard);
    }

    return 0;
}