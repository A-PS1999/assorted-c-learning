#include "langtons_ant.h"
#include <string.h>

void initBoard(Board* board) {
    board->height = BOARD_HEIGHT;
    board->width = BOARD_WIDTH;

    memset(board->board, ' ', BOARD_HEIGHT*BOARD_WIDTH*sizeof(board->board[0][0]));

    for (int row=0; row < board->height; row++) {
        board->board[row][board->width-1] = '\0';
    }
}

void updateBoard(Board* board) {

}

void printBoard(Board* board) {

    for (int row=0; row < board->height; row++) {
        printf("%s\n", board->board[row]);
    }

}
