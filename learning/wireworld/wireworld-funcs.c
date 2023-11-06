#include "wireworld.h"
#include <unistd.h>
#include <string.h>

void setBlankBoard(Board* board);
int searchNeighbours(Board* currBoard, int x, int y);
int checkCell(Board* board, int checkX, int checkY);

bool isValidInput(int argc, char** argv) {
    if (argc != 2) {
        return false;
    }

    if (access(argv[1], F_OK) != 0) {
        return false;
    }

    return true;
}

bool initBoard(Board* wireBoard, char* fileName) {
    FILE* file;

    file = fopen(fileName, "r");

    if (!file) {
        return false;
    }

    wireBoard->height = BOARD_HEIGHT;
    wireBoard->width = BOARD_WIDTH;

    char fileBuffer[FILE_BUFFER_LINE_LEN];

    int currRow = 0;

    while (fgets(fileBuffer, FILE_BUFFER_LINE_LEN, file) && currRow < wireBoard->height) {
        
        for (int currCol = 0; currCol < wireBoard->width-1; currCol++) {
            wireBoard->board[currRow][currCol] = fileBuffer[currCol];
        }

        currRow++;
    }

    currRow = 0;

    for (; currRow < wireBoard->height; currRow++) {
        wireBoard->board[currRow][wireBoard->width-1] = '\0';
    }

    fclose(file);
    return true;
}

void setBlankBoard(Board* board) {

    memset(board->board, ' ', BOARD_HEIGHT*BOARD_WIDTH*sizeof(board->board[0][0]));

    for (int row = 0; row < BOARD_HEIGHT; row++) {
        board->board[row][(BOARD_WIDTH)-1] = '\0';
    }
}

int checkCell(Board* board, int checkX, int checkY) {
    if (checkX >= 0 && checkX < board->width-1 && checkY >= 0 && checkY < board->height) {
        if (board->board[checkY][checkX] == 'H') {
            return 1;
        } else {
            return 0;
        }
    }

    return 0;
}

int searchNeighbours(Board* currBoard, int x, int y) {

    int res = 0;

    res += checkCell(currBoard, x+1, y);
    res += checkCell(currBoard, x, y+1);
    res += checkCell(currBoard, x+1, y+1); 
    res += checkCell(currBoard, x-1, y-1);
    res += checkCell(currBoard, x-1, y);
    res += checkCell(currBoard, x, y-1);
    res += checkCell(currBoard, x+1, y-1);
    res += checkCell(currBoard, x-1, y+1);

    return res;
}

void updateBoard(Board* wireBoard) {

    Board nextBoard;

    setBlankBoard(&nextBoard);

    int numNeighbourElectronHeads;

    for (int row=0; row < wireBoard->height; row++) {
        for (int col=0; col < wireBoard->width-1; col++) {
            char currCellVal = wireBoard->board[row][col];

            switch (currCellVal) {
                case ' ':
                    continue;
                    break;
                case 'H':
                    nextBoard.board[row][col] = 't';
                    break;
                case 't':
                    nextBoard.board[row][col] = 'c';
                    break;
                case 'c':
                    numNeighbourElectronHeads = searchNeighbours(wireBoard, col, row);

                    if (numNeighbourElectronHeads == 1 || numNeighbourElectronHeads == 2) {
                        nextBoard.board[row][col] = 'H';
                    } else {
                        nextBoard.board[row][col] = 'c';
                    }
                    break;
                default:
                    assert(false);
                    break;
            }
        }
    }

    memcpy(&wireBoard->board, &nextBoard.board, sizeof(wireBoard->board));
}

void printBoard(Board* wireBoard) {

    for (int row=0; row < wireBoard->height; row++) {
        printf("%s\n", wireBoard->board[row]);
    }
    printf("----------------------------------------\n");

}