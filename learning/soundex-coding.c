#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define SOUNDEX_ARR_SIZE 5

void genSoundexCode(char* array, char* name);
int handleLetterCases(char currLetter);
bool isIncomplete(char* soundexArr);
void fillWithZeroes(char* array);

int main(void) {

    char soundexCode[SOUNDEX_ARR_SIZE] = {'*'};

    genSoundexCode(soundexCode, "Washington");
    assert(strcmp(soundexCode, "W252") == 0);
    genSoundexCode(soundexCode, "Wu");
    assert(strcmp(soundexCode, "W000") == 0);
    genSoundexCode(soundexCode, "DeSmet");
    assert(strcmp(soundexCode, "D253") == 0);
    genSoundexCode(soundexCode, "Gutierrez");
    assert(strcmp(soundexCode, "G362") == 0);
    genSoundexCode(soundexCode, "Pfister");
    assert(strcmp(soundexCode, "P236") == 0);
    genSoundexCode(soundexCode, "Jackson");
    assert(strcmp(soundexCode, "J250") == 0);
    genSoundexCode(soundexCode, "Tymczak");
    assert(strcmp(soundexCode, "T522") == 0);
    genSoundexCode(soundexCode, "Ashcraft");
    assert(strcmp(soundexCode, "A261") == 0);
    genSoundexCode(soundexCode, "Hilbert");
    assert(strcmp(soundexCode, "H416") == 0);
    genSoundexCode(soundexCode, "Wheaton");
    assert(strcmp(soundexCode, "W350") == 0);
    genSoundexCode(soundexCode, "Heilbronn");
    assert(strcmp(soundexCode, "H416") == 0);
    genSoundexCode(soundexCode, "O'Hara");
    assert(strcmp(soundexCode, "O600") == 0);
    genSoundexCode(soundexCode, "Lissajous");
    assert(strcmp(soundexCode, "L222") == 0);

    printf("All test cases passed!\n");

    return 0;
}

void genSoundexCode(char* array, char* name) {
    if (!isIncomplete(array)) {
        memset(array, '*', SOUNDEX_ARR_SIZE-1);
    }

    char* currLetter = name;
    int currCode;
    int prevCode = handleLetterCases(toupper(*currLetter));
    int soundexIdx = 0;

    array[soundexIdx++] = *currLetter;
    currLetter++;

    while (soundexIdx < 4 && *currLetter) {
        char letterToUpper = (toupper(*currLetter));
        currCode = handleLetterCases(letterToUpper);

        if (currCode == prevCode) {
            currLetter++;
            continue;
        }

        if (currCode == -1) {
            prevCode = letterToUpper == 'H' ? prevCode : 0;
            currLetter++;
        } else {
            array[soundexIdx] = currCode + '0';
            prevCode = currCode;
            soundexIdx++;
            currLetter++;
        }
    }

    if (isIncomplete(array)) {
        fillWithZeroes(array);
    }

    array[SOUNDEX_ARR_SIZE] = '\0';
}

void fillWithZeroes(char* array) {
    int idx = 0;

    while (isalpha(array[idx]) || isdigit(array[idx])) {
        idx++;
    }

    for (idx; idx < SOUNDEX_ARR_SIZE-1; idx++) {
        array[idx] = '0';
    }
}

bool isIncomplete(char* soundexArr) {
    for (int i=0; i < SOUNDEX_ARR_SIZE-1; i++) {
        if (soundexArr[i] == '*') {
            return true;
        }
    }

    return false;
}

int handleLetterCases(char currLetter) {
    switch (currLetter) {
        case 'B':
        case 'F':
        case 'P':
        case 'V':
            return 1;
            break;
        case 'C':
        case 'G':
        case 'J':
        case 'K':
        case 'Q':
        case 'S':
        case 'X':
        case 'Z':
            return 2;
            break;
        case 'D':
        case 'T':
            return 3;
            break;
        case 'L':
            return 4;
            break;
        case 'M':
        case 'N':
            return 5;
            break;
        case 'R':
            return 6;
            break;
        default:
            return -1;
            break;
    }
}