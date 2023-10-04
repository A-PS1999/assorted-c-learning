#include "crosswords.h"
#include <assert.h>

#define NUM_BUFFER_LEN 12

typedef enum CrosswordPath { ACROSS, DOWN, BOTH, NONE } CrosswordPath;

CrosswordPath getCrosswordPath(int i, int j, const crossword* c);
char getCellContent(int i, int j, int size, const crossword* c);
void handleIntToStr(char* array, int* index, int num);

void test(void) {
    
}

bool str2crossword(int sz, char* ip, crossword* cw) {
    if (ip == NULL || sz <= 0 || (sz*sz) != (int)strlen(ip)) return false;
    if (cw == NULL) return false;

    cw->sz = sz;

    char* ptr = ip;

    for (int i=0; i < sz; i++) {
        for (int j=0; j < sz; j++) {
            cw->arr[i][j] = *ptr;
            ptr++;
        }
    }

    return true;
}

void getcluestring(const crossword* c, char* str) {
    int size = c->sz;

    int num = 1;

    char acrossVals[BIGSTR] =  {"A"};
    char downVals[BIGSTR] =  {"D"};
    int acrossStrIdx = 1;
    int downStrIdx = 1;

    for (int i=0; i < size; i++) {
        for (int j=0; j < size; j++) {
            if (c->arr[i][j] == ' ' || c->arr[i][j] == '.') {
                switch (getCrosswordPath(i, j, c)) {
                    case BOTH:
                        acrossVals[acrossStrIdx++] = '-';
                        downVals[downStrIdx++] = '-';
                        handleIntToStr(acrossVals, &acrossStrIdx, num);
                        handleIntToStr(downVals, &downStrIdx, num);
                        num++;
                        break;
                    case ACROSS:
                        acrossVals[acrossStrIdx++] = '-';
                        handleIntToStr(acrossVals, &acrossStrIdx, num);
                        num++;
                        break;
                    case DOWN:
                        downVals[downStrIdx++] = '-';
                        handleIntToStr(downVals, &downStrIdx, num);
                        num++;
                        break;
                    case NONE:
                        break;
                    default:
                        assert(false);
                        break;
                }
            }
        }
    }

    acrossVals[acrossStrIdx] = '|';

    strcpy(str, acrossVals);
    strcat(str, downVals);
}

int getchecked(crossword c) {
    
    int size = c.sz;
    int totalEmpty = 0;
    int totalChecked = 0;
    char valAbove;
    char valToLeft;

    for (int i=0; i < size; i++) {
        for (int j=0; j < size; j++) {
            if (c.arr[i][j] == ' ' || c.arr[i][j] == '.') {
                totalEmpty++;
                switch (getCrosswordPath(i, j, &c)) {
                    case BOTH:
                        totalChecked++;
                        break;
                    case ACROSS:
                        valAbove = getCellContent(i-1, j, size, &c);
                        if (valAbove == ' ' || valAbove == '.') {
                            totalChecked++;
                        }
                        break;
                    case DOWN:
                        valToLeft = getCellContent(i, j-1, size, &c);
                        if (valToLeft == ' ' || valToLeft == '.') {
                            totalChecked++;
                        }
                        break;
                    case NONE:
                        valToLeft = getCellContent(i, j-1, size, &c);
                        valAbove = getCellContent(i-1, j, size, &c);
                        if ((valToLeft == ' ' || valToLeft == '.') && (valAbove == ' ' || valAbove == '.')) {
                            totalChecked++;
                        }
                        break;
                    default:
                        assert(false);
                        break;
                }
            }
        }
    }

    int res = round((totalChecked/(double)totalEmpty) * 100);

    return res;
}

CrosswordPath getCrosswordPath(int i, int j, const crossword* c) {
    int size = c->sz;

    char prevColVal = getCellContent(i, j-1, size, c);
    char prevRowVal = getCellContent(i-1, j, size, c);
    char nextRowVal = getCellContent(i+1, j, size, c);
    char nextColVal = getCellContent(i, j+1, size, c);

    if ((prevColVal == '\0' || (prevColVal == '*' || prevColVal == 'X')) && (nextColVal != '\0' && nextColVal != '*' && nextColVal != 'X')) {
        if ((prevRowVal == '\0' || (prevRowVal == '*' || prevRowVal == 'X')) && (nextRowVal != '\0' && nextRowVal != '*' && nextRowVal != 'X')) {
            return BOTH;
        }

        return ACROSS;
    } else if (((prevRowVal == '\0' || (prevRowVal == '*' || prevRowVal == 'X')) && (nextRowVal != '\0' && nextRowVal != '*' && nextRowVal != 'X'))) {
        return DOWN;
    } else {
        return NONE;
    }
}

char getCellContent(int i, int j, int size, const crossword* c) {
    if (i >= 0 && i < size && j >= 0 && j < size) {
        return c->arr[i][j];
    } else {
        return '\0';
    }
}

void handleIntToStr(char* array, int* index, int num) {
    char buffer[NUM_BUFFER_LEN];

    snprintf(buffer, NUM_BUFFER_LEN, "%d", num);

    int numLen = strlen(buffer);

    strcat(array, buffer);

    *index += numLen;
}