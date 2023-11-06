#include "anagrams.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define ASCII_CHAR_BASE 97
#define LONGEST_WORD_LEN 100
#define ALPHABET_LEN 26

void createHistogram(char* word, int* hist);
bool areAnagrams(size_t inputLen, int* inputHist, char* str);

bool isValidInput(int argc, char** argv) {
    if (argc != 2) return false;

    char* testStr = argv[1];

    while (*testStr != '\0') {
        if (!isalpha((unsigned int)*testStr)) {
            return false;
        }

        testStr++;
    }

    return true;
}

void createHistogram(char* word, int* hist) {
    
    char* currChar = word;

    while (*currChar) {
        hist[(*currChar) - 'a'] += 1;
        currChar++;
    }
}

bool areAnagrams(size_t inputLen, int* inputHist, char* str) {
    size_t otherLen;
    int otherHist[ALPHABET_LEN] = {0};

    otherLen = (strlen(str))-1;
    createHistogram(str, otherHist);

    if (otherLen != inputLen) {
        return false;
    }

    for (int i=0; i < ALPHABET_LEN; i++) {
        if (inputHist[i] != otherHist[i]) {
            return false;
        }
    }

    return true;
}

bool doAnagramSearch(char* input) {

    size_t inputLen;

    int inputHist[ALPHABET_LEN] = {0};
    inputLen = strlen(input);
    createHistogram(input, inputHist);

    static const char fileName[] = "words_alpha.txt"; 

    FILE* file;

    file = fopen(fileName, "r");

    if (!file) {
        return false;
    }

    char fileBuffer[LONGEST_WORD_LEN];

    while (fgets(fileBuffer, LONGEST_WORD_LEN, file)) {
        if (strcmp(input, fileBuffer) == 0) continue;

        if (areAnagrams(inputLen, inputHist, fileBuffer)) {
            printf("%s\n", fileBuffer);
        }
    }

    return true;
}
