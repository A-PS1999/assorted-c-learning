#include "life-wars.h"

int main(int argc, char** argv) {
    if (!isValidInput(argc, argv)) {
        perror("Error - Invalid inputs provided");
        return -1;
    }

    srand(time(NULL));

    Board gameBoard;

    int currGame = 0;
    int playerATotal = 0;
    int playerBTotal = 0;
    bool firstInit = true;

    while (currGame < TOTAL_GAMES) {
        if (!setBoardStart(&gameBoard, argv[1], argv[2], &firstInit)) {
            perror("Error - Failed to set game board");
            return -1;
        }
        playGame(&gameBoard, &playerATotal, &playerBTotal);
        printGameStats(currGame, &gameBoard, playerATotal, playerBTotal);
        currGame++;
    }

    printWinner(playerATotal, playerBTotal);

    free(gameBoard.playerAStarts);
    free(gameBoard.playerBStarts);

    return 0;
}