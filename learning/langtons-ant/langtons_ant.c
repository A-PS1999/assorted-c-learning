#include "langtons_ant.h"

int main(void) {

    Board simBoard;

    initBoard(&simBoard);

    int iterations = 0;

    while (iterations < NUM_ITERATIONS) {
        printBoard(&simBoard);
        updateBoard(&simBoard);

        printf("Enter a character to continue.\n");
        getchar();
        iterations++;
    }

    return 0;
}
