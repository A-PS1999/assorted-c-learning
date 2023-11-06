#include "maze-escape.h"

bool isValidInput(int argc, char** argv, int* mazeWidth, int* mazeHeight) {
    if (argc != 2) {
        return false;
    }

    char* widthStr;
    char* heightStr;
    int width, height;

    FILE* file;

    file = fopen(argv[1], "r");

    if (!file) {
        perror("Error: Failed to open file");
        exit(EXIT_FAILURE);
    }

    char sizeBuffer[SIZEBUFFER_LEN];
    fgets(sizeBuffer, SIZEBUFFER_LEN, file);
    widthStr = strtok(sizeBuffer, " ");
    heightStr = strtok(NULL, " ");

    width = atoi(widthStr);
    height = atoi(heightStr);

    if (width > 20 || height > 20 || width <= 0 || height <= 0) {
        return false;
    }

    *mazeWidth = width;
    *mazeHeight = height;

    fclose(file);
    return true;
}

Maze* initMaze(char* fileName, int width, int height) {
    Maze* newMaze;

    FILE* file;

    file = fopen(fileName, "r");

    if (!file) {
        perror("Error: Failed to open file");
        exit(EXIT_FAILURE);
    }

    if ((newMaze = malloc(sizeof(Maze))) == NULL) {
        perror("Error: Failed to allocate memory for maze struct");
        exit(EXIT_FAILURE);
    }

    if ((newMaze->maze = calloc(height, sizeof(char*))) == NULL) {
        perror("Error: Failed to allocate maze array");
        exit(EXIT_FAILURE);
    }
    for (int row=0; row < height; row++) {
        if ((newMaze->maze[row] = calloc(width+1, sizeof(char))) == NULL) {
            perror("Error: Failed to allocate maze array");
            exit(EXIT_FAILURE);
        }
    }

    char* fileBuffer;
    if ((fileBuffer = malloc(width+1)) == NULL) {
        perror("Error: Failed to allocate filebuffer");
        exit(EXIT_FAILURE);
    }

    fgets(fileBuffer, width+1, file);
    int rowIdx=0;
    while (fgets(fileBuffer, width+1, file) && rowIdx < height) {
        if (fileBuffer[0] != '\n') {
            strcpy(newMaze->maze[rowIdx], fileBuffer);
            rowIdx++;
        }
    }

    newMaze->height = height;
    newMaze->width = width;

    fclose(file);
    free(fileBuffer);
    return newMaze;
}

void solveMaze(Maze* maze, bool* solved) {

    XYPos startPos = getStartPos(maze);
    if (startPos.y == -1) {
        return;
    }

    recurseMaze(maze, startPos.x, startPos.y, solved);
    floodFillWalls(maze, startPos.x, startPos.y);
}

void recurseMaze(Maze* maze, int posX, int posY, bool* solved) {
    if (maze->maze[posY][posX] == '*') {
        return;
    }
    if (posX == maze->width-1 && maze->maze[posY][posX] == ' ') {
        *solved = true;
        maze->maze[posY][posX] = '.';
        return;
    }
    maze->maze[posY][posX] = '*';

    int neighbours[NEIGHBOURARR_LEN][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    for (int i=0; i < NEIGHBOURARR_LEN; i++) {
        int newX = posX + neighbours[i][0];
        int newY = posY + neighbours[i][1];

        if (isInBounds(maze, newY, newX)) {
            if (isUnvisitedSpace(maze, newY, newX)) {
                maze->maze[posY][posX] = '*';
                recurseMaze(maze, newX, newY, solved);
            }
        }
    }

    maze->maze[posY][posX] = '.';
}

void recurseWalls(Maze* maze, int posX, int posY, char fillChar) {
    if (maze->maze[posY][posX] == 'A' || maze->maze[posY][posX] == 'B') {
        return;
    }
    maze->maze[posY][posX] = fillChar;

    int neighbours[NEIGHBOURARR_LEN][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    for (int i=0; i < NEIGHBOURARR_LEN; i++) {
        int newX = posX + neighbours[i][0];
        int newY = posY + neighbours[i][1];

        if (isInBounds(maze, newY, newX)) {
            if (maze->maze[newY][newX] == '#') {
                recurseWalls(maze, newX, newY, fillChar);
            }
        }
    }
}

void floodFillWalls(Maze* maze, int startX, int startY) {
    recurseWalls(maze, startX, startY-1, 'A');
    recurseWalls(maze, startX, startY+1, 'B');
}

XYPos getStartPos(Maze* maze) {
    XYPos res;
    res.x = -1;
    res.y = -1;

    for (int row=0; row < maze->height; row++) {
        if (maze->maze[row][0] == ' ') {
            res.x = 0;
            res.y = row;
        } 
    }

    return res;
}

void printMaze(Maze* maze) {

    for (int row=0; row < maze->height; row++) {
        printf("%s\n", maze->maze[row]);
    }

}

void freeMaze(Maze* maze) {
    
    for (int row=0; row < maze->height; row++) {
        free(maze->maze[row]);
    }

    maze->height = 0;
    maze->width = 0;
    free(maze);
}

bool isInBounds(Maze* maze, int row, int col) {
    int width = maze->width;
    int height = maze->height;

    return (row >= 0 && row < height && col >= 0 && col < width);
}

bool isUnvisitedSpace(Maze* maze, int row, int col) {
    if (maze->maze[row][col] == ' ') {
        return true;
    }

    return false;
}
