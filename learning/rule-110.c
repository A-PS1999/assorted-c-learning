#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define ARR_SIZE 34
#define MAX_ITERATIONS 34

typedef enum AutomataRuleset { ONETEN = 0, THIRTY, NINETY } AutomataRuleset;

void printBasicInstructions();
void printSelectionOptions();
void setupRandomArray(int* array);
void setupMiddleStartArray(int* array);
void printAutomataLine(int array[]);
void updateAutomata(int* prev, int* curr, AutomataRuleset selection);
void setBitfield(uint8_t* field, int i, int* prev);
void copyCurrToPrev(int* prev, int* curr);
int handleCases(AutomataRuleset selection, uint8_t bitfield);
int handle110Cases(uint8_t bitfield);
int handle30Cases(uint8_t bitfield);
int handle90Cases(uint8_t bitfield);

int main(void) {
    int prev[ARR_SIZE] = {0};
    int curr[ARR_SIZE] = {0};

    srand(time(NULL));

    int inputChoice;
    AutomataRuleset rulesetSelection = ONETEN;

    printBasicInstructions();

    do {
        scanf(" %d", &inputChoice);
    } while (inputChoice < 0 || inputChoice > 1);

    printSelectionOptions();

    do {
        scanf(" %d", &rulesetSelection);
    } while (rulesetSelection != ONETEN && rulesetSelection != THIRTY && rulesetSelection != NINETY);

    switch (inputChoice) {
        case 0:
            setupRandomArray(prev);
            break;
        case 1:
            setupMiddleStartArray(prev);
            break;
        default:
            printf("Uh oh, you weren't supposed to be able to give that input!\n");
            exit(EXIT_FAILURE);
            break;
    }

    printAutomataLine(prev);

    for (int n=0; n < MAX_ITERATIONS; n++) {
        updateAutomata(prev, curr, rulesetSelection);
        printAutomataLine(curr);
    }

    return 0;
}

void printBasicInstructions() {
    printf("This program will generate a pattern with cellular automata.\n");
    printf("\n");
    printf("Would you like to generate a random sequence or start with a single activated cell in the middle?\n");
    printf("0 = random sequence\n");
    printf("1 = activate a single cell in the middle\n");
}

void printSelectionOptions() {
    printf("Now, which cellular automata ruleset would you like to use?\n");
    printf("\n");
    printf("0 = Rule 110\n");
    printf("1 = Rule 30\n");
    printf("2 = Rule 90\n");
}

void setupRandomArray(int* array) {
    for (int i=0; i < ARR_SIZE; i++) {
        array[i] = (rand() < RAND_MAX/2);
    }
}

void setupMiddleStartArray(int* array) {
    array[17] = 1;
}

void printAutomataLine(int array[]) {
    for (int i=0; i < ARR_SIZE; i++) {
        switch (array[i]) {
            case 0:
                printf(" ");
                break;
            case 1:
                printf("#");
                break;
            default:
                break;
        }
    }
    printf("\n");
}

void updateAutomata(int* prev, int* curr, AutomataRuleset selection) {
    for (int i=0; i < ARR_SIZE; i++) {
        uint8_t bitfield = 0;

        if ((i-1 >= 0) && (i+1 < ARR_SIZE)) {
            setBitfield(&bitfield, i, prev);
            curr[i] = handleCases(selection, bitfield);
        } else {
            curr[i] = 0;
        }
    }
    copyCurrToPrev(prev, curr);
}

void setBitfield(uint8_t* field, int i, int* prev) {
    if (prev[i-1] == 1) {
        *field |= 0x04;
    }
    if (prev[i] == 1) {
        *field |= 0x02;
    }
    if (prev[i+1] == 1) {
        *field |= 0x01;
    }
}

void copyCurrToPrev(int* prev, int* curr) {
    for (int m=0; m < ARR_SIZE; m++) {
        prev[m] = curr[m];
    }
}

int handleCases(AutomataRuleset selection, uint8_t bitfield) {
    switch (selection) {
        case ONETEN:
            return handle110Cases(bitfield);
            break;
        case THIRTY:
            return handle30Cases(bitfield);
            break;
        case NINETY:
            return handle90Cases(bitfield);
            break;
        default:
            return handle110Cases(bitfield);
            break;
    }
}

int handle110Cases(uint8_t bitfield) {
    /*
        0x07 = 111
        0x06 = 110
        0x05 = 101
        0x04 = 100
        0x03 = 011
        0x02 = 010
        0x01 = 001
    */

    if ((bitfield ^ 0x07) == 0) {
        return 0;

    } else if ((bitfield ^ 0x06) == 0) {
        return 1;
    } else if ((bitfield ^ 0x05) == 0) {
        return 1;
    } else if ((bitfield ^ 0x04) == 0) {
        return 0;
    } else if ((bitfield ^ 0x03) == 0) {
        return 1;
    } else if ((bitfield ^ 0x02) == 0) {
        return 1;
    } else if ((bitfield ^ 0x01) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int handle30Cases(uint8_t bitfield) {
    /*
        0x07 = 111
        0x06 = 110
        0x05 = 101
        0x04 = 100
        0x03 = 011
        0x02 = 010
        0x01 = 001
    */

    if ((bitfield ^ 0x07) == 0) {
        return 0;

    } else if ((bitfield ^ 0x06) == 0) {
        return 0;
    } else if ((bitfield ^ 0x05) == 0) {
        return 0;
    } else if ((bitfield ^ 0x04) == 0) {
        return 1;
    } else if ((bitfield ^ 0x03) == 0) {
        return 1;
    } else if ((bitfield ^ 0x02) == 0) {
        return 1;
    } else if ((bitfield ^ 0x01) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int handle90Cases(uint8_t bitfield) {
    /*
        0x07 = 111
        0x06 = 110
        0x05 = 101
        0x04 = 100
        0x03 = 011
        0x02 = 010
        0x01 = 001
    */

    if ((bitfield ^ 0x07) == 0) {
        return 0;

    } else if ((bitfield ^ 0x06) == 0) {
        return 1;
    } else if ((bitfield ^ 0x05) == 0) {
        return 0;
    } else if ((bitfield ^ 0x04) == 0) {
        return 1;
    } else if ((bitfield ^ 0x03) == 0) {
        return 1;
    } else if ((bitfield ^ 0x02) == 0) {
        return 0;
    } else if ((bitfield ^ 0x01) == 0) {
        return 1;
    } else {
        return 0;
    }
}