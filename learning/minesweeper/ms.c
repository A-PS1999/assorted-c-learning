#include "ms.h"

typedef struct Counts {
    int mineCount;
    int unkCount;
} Counts;

bool isSolved(board* b);
void applyRuleOne(board* b);
void applyRuleTwo(board* b, int* numMines, bool* ruleFlag);
Counts countNeighbours(board* b, int x, int y);
void fillUnknowns(board* b, int x, int y);
bool isInBounds(board* b, int x, int y);

#define COUNTED_MINE '*'

board solve_board(board b) {

    int foundMines = 0;
    bool ruleApplied;

    // ruleApplied flag is used to loop until we find
    // that board cannot be solved
    do {
        ruleApplied = false;
        if (foundMines != b.totmines) {
            applyRuleTwo(&b, &foundMines, &ruleApplied);
        }
        if (foundMines == b.totmines) {
            applyRuleOne(&b);
        }
    } while (ruleApplied == true && !isSolved(&b));
    
    return b;
}

void board2str(char s[MAXSQ*MAXSQ+1], board b) {
    int width = b.w;
    int height = b.h;

    int strIdx = 0;

    for (int row=0; row < height; row++) {
        for (int col=0; col < width; col++) {
            s[strIdx] = b.grid[row][col];

            // Convert counted mine chars back to X for final strcmp
            if (s[strIdx] == COUNTED_MINE) {
                s[strIdx] = MINE;
            }

            strIdx++;
        }
    }
    s[strIdx] = '\0';
}

bool syntax_check(unsigned totmines, unsigned width, unsigned height, char inp[MAXSQ*MAXSQ+1]) {
    int expectedLen = width * height;

    if (strlen(inp) != (unsigned long)expectedLen) {
        return false;
    }

    char* testString = inp;

    unsigned int minesFound = 0;

    while (*testString != '\0') {
        if ((!isdigit((unsigned)*testString))) {
            if (*testString != MINE && *testString != UNK) {
                return false;
            }
        } else if (*testString == '9') {
            return false;
        }

        if (*testString == MINE) {
            minesFound++;
        }

        testString++;
    }

    return (minesFound <= totmines);
}

board make_board(int totmines, int width, int height, char inp[MAXSQ*MAXSQ+1]) {
    board outputBoard;

    outputBoard.w = width;
    outputBoard.h = height;
    outputBoard.totmines = totmines;

    char* stringPtr = inp;

    for (int row=0; row < height; row++) {
        for (int col=0; col < width; col++) {
            outputBoard.grid[row][col] = *stringPtr;
            stringPtr++;
        }
    }

    return outputBoard;
}

void applyRuleOne(board* b) {

    for (int row=0; row < b->h; row++) {
        for (int col=0; col < b->w; col++) {
            if (b->grid[row][col] == UNK) {
                Counts res;
                res = countNeighbours(b, col, row);
                b->grid[row][col] = res.mineCount + '0';
            }
        }
    }

}

void applyRuleTwo(board* b, int* numMines, bool* ruleFlag) {

    for (int row=0; row < b->h; row++) {
        for (int col=0; col < b->w; col++) {
            
            int currCell = b->grid[row][col];

            if (currCell == MINE) {
                *numMines += 1;
                // To avoid double counting, we change the char
                b->grid[row][col] = COUNTED_MINE;
            } else if (isdigit(currCell)) {
                Counts res;
                res = countNeighbours(b, col, row);
                if (res.unkCount > 0) {
                    int numToFill;
                    numToFill = (currCell - '0') - res.unkCount;
    
                    if (numToFill == res.mineCount) {
                        fillUnknowns(b, col, row);
                        *ruleFlag = true;
                    }
                }
            }
        }
    }
}

Counts countNeighbours(board* b, int x, int y) {
    Counts counts;
    counts.mineCount = 0;
    counts.unkCount = 0;    

    for (int row=y-1; row <= y+1; row++) {
        for (int col=x-1; col <= x+1; col++) {

            if (isInBounds(b, col, row) && !(row == y && col == x)) {
                int val = b->grid[row][col];
                if (val == MINE || val == COUNTED_MINE) {
                    counts.mineCount++;
                } else if (val == UNK) {
                    counts.unkCount++;
                }
            }
        }
    }

    return counts;
}

void fillUnknowns(board* b, int x, int y) {

    for (int row=y-1; row <= y+1; row++) {
        for (int col=x-1; col <= x+1; col++) {
            if (isInBounds(b, col, row) && !(row == y && col == x)) {
                if (b->grid[row][col] == UNK) {
                    b->grid[row][col] = MINE;
                }
            }
        }
    }
}

bool isInBounds(board* b, int x, int y) {
    if (x >= 0 && x < b->w && y >= 0 && y < b->h) {
        return true;
    }

    return false;
}

bool isSolved(board* b) {

    for (int row=0; row < b->h; row++) {
        for (int col=0; col < b->w; col++) {
            if (b->grid[row][col] == UNK) {
                return false;
            }
        }
    }

    return true;
}

void test(void) {
    board b;
    Counts neighbourCounts;
    int numMines = 0;
    bool ruleFlag = false;
    char str[MAXSQ*MAXSQ+1];

    b = make_board(3, 5, 5, "?110?1?2101?X?1012?1?0111");

    assert(isSolved(&b) == false);
    assert(isInBounds(&b, 0, 0) == true);
    assert(isInBounds(&b, 2, 1) == true);
    assert(isInBounds(&b, 4, 4) == true);
    assert(isInBounds(&b, 5, 1) == false);
    assert(isInBounds(&b, -1, 2) == false);
    assert(isInBounds(&b, 5, 5) == false);

    neighbourCounts = countNeighbours(&b, 2, 1);
    assert(neighbourCounts.mineCount == 1);
    assert(neighbourCounts.unkCount == 3);

    neighbourCounts = countNeighbours(&b, 4, 4);
    assert(neighbourCounts.mineCount == 0);
    assert(neighbourCounts.unkCount == 1);

    neighbourCounts = countNeighbours(&b, 5, 5);
    assert(neighbourCounts.mineCount == 0);
    assert(neighbourCounts.unkCount == 0);

    applyRuleTwo(&b, &numMines, &ruleFlag);
    assert(ruleFlag == true);
    assert(numMines == 2);
    assert(isSolved(&b) == false);
    ruleFlag = false;
    applyRuleTwo(&b, &numMines, &ruleFlag);
    assert(numMines == 3);
    applyRuleOne(&b);
    assert(isSolved(&b) == true);

    b = make_board(3, 5, 5, "11?0?X1111111X?11?11?X10?");

    assert(isSolved(&b) == false);
    applyRuleOne(&b);
    assert(isSolved(&b) == true);

    b = make_board(1, 1, 1, "X");
    neighbourCounts = countNeighbours(&b, 0, 0);
    assert(neighbourCounts.mineCount == 0);
    assert(neighbourCounts.unkCount == 0);

    b = make_board(3, 5, 5, "?110?1?2101?X?1012?1?0111");
    fillUnknowns(&b, 2, 1);
    assert(b.grid[1][1] == MINE);
    assert(b.grid[2][1] == MINE);
    assert(b.grid[2][3] == MINE);
    assert(b.grid[1][3] != MINE);

    char bigGrid[] = 
        "?12345638X"
        "876543210?"
        "?12345678X"
        "876549810?"
        "?12345678X"
        "876?47210?"
        "?12345678X"
        "8760274?0?"
        "?121?2678X"
        "8760X3410?";

    assert(syntax_check(2, 10, 10, bigGrid) == false);
    b = make_board(2, 10, 10, bigGrid);
    assert(b.w == 10);
    assert(b.totmines == 2);
    board2str(str, b);
    assert(strcmp(str, bigGrid)==0);

    // Testing rule 1 on a rectangular grid
    strcpy(str, "?1?X2X21?1X?12?X10");
    assert(syntax_check(4, 9, 2, str) == true);
    b = make_board(4, 9, 2, str);
    b = solve_board(b);
    board2str(str, b);
    assert(strcmp(str, "112X2X2101X2122X10")==0);

    // Testing the use of both rules on a rectangular grid
    strcpy(str, "?1?X2?21?1X?122X10");
    assert(syntax_check(4, 9, 2, str) == true);
    b = make_board(4, 9, 2, str);
    b = solve_board(b);
    board2str(str, b);
    assert(strcmp(str, "112X2X2101X2122X10")==0);

    strcpy(str, "?1110?112X2?11?0");
    assert(syntax_check(3, 2, 8, str) == true);
    b = make_board(3, 2, 8, str);
    b = solve_board(b);
    board2str(str, b);
    assert(strcmp(str, "X11100112X2X1100")==0);

    // Testing the rules on an unsolveable rectangular board
    strcpy(str, "X?X?X?X?X?X???????4?4?4?");
    assert(syntax_check(4, 6, 4, str) == false);
    assert(syntax_check(12, 6, 4, str) == true);
    b = make_board(12, 6, 4, str);
    b = solve_board(b);
    board2str(str, b);
    assert(strcmp(str, "X?X?X?X?X?X???????4?4?4?")==0);

    strcpy(str, "xa02@?X1X");
    assert(syntax_check(4, 3, 3, str)==false);
    strcpy(str, "X1001X11X2X");
    assert(syntax_check(3, 2, 2, str)==false);

    char bigGridTwo[] =
        "XXXX?XXXX"
        "4664?4664"
        "XXXX?XXXX"
        "?????????"
        "XXXX?XXXX"
        "4664?4664"
        "XXXX?XXXX";

    char bigGridTwoSolved[] =
        "XXXX2XXXX"
        "466444664"
        "XXXX2XXXX"
        "466444664"
        "XXXX2XXXX"
        "466444664"
        "XXXX2XXXX";

    strcpy(str, bigGridTwo);
    b = make_board(32, 9, 7, str);
    applyRuleOne(&b);
    board2str(str, b);
    assert(strcmp(str, bigGridTwoSolved)==0);
}
