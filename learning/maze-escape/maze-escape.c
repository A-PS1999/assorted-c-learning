#include "maze-escape.h"

int main(int argc, char** argv) {
    int mazeWidth;
    int mazeHeight;

    if (!isValidInput(argc, argv, &mazeWidth, &mazeHeight)) {
        perror("Error: Invalid inputs provided or failed to open file");
        exit(EXIT_FAILURE);
    }

    Maze* theMaze;
    theMaze = initMaze(argv[1], mazeWidth, mazeHeight);
    bool mazeSolved = false;

    solveMaze(theMaze, &mazeSolved);

    if (mazeSolved) {
        printMaze(theMaze);
    } else {
        printf("This maze could not be solved!\n");
        return 1;
    }

    freeMaze(theMaze);

    return 0;
}