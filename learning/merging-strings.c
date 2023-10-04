#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

void stringMerge(const char* stringOne, const char* stringTwo, char* array);

#define STRING_MAX_LEN 1000

int main(void) {

    char string[STRING_MAX_LEN];
    
    stringMerge("Hello World!", "World! & Everyone.", string);
    assert(strcmp(string, "Hello World! & Everyone.") == 0);

    stringMerge("The cat sat", "sat on the mat.", string);
    assert(strcmp(string, "The cat sat on the mat.") == 0);

    stringMerge("The cat sat on the mat", "The cat sat on the mat.", string);
    assert(strcmp(string, "The cat sat on the mat.") == 0);

    stringMerge("One ", "Two", string);
    assert(strcmp(string, "One Two") == 0);

    stringMerge("", "The cat sat on the mat.", string);
    assert(strcmp(string, "The cat sat on the mat.") == 0);

    stringMerge("The cat sat on the mat.", "", string);
    assert(strcmp(string, "The cat sat on the mat.") == 0);

    stringMerge("123412341234", "1234", string);
    assert(strcmp(string, "123412341234") == 0);

    printf("All test cases passed!\n");

    return 0;
}

void stringMerge(const char* stringOne, const char* stringTwo, char* array) {
    size_t stringOneLen = strlen(stringOne);
    size_t stringTwoLen = strlen(stringTwo);

    // Handle trivial cases where we only have one real input
    if (stringOneLen == 0) {
        strcpy(array, stringTwo);
        return;
    } else if(stringTwoLen == 0) {
        strcpy(array, stringOne);
        return;
    }

    // To iterate over pointers to the strings, we need to copy the const char* into regular char*
    char* strOneCopy = calloc(strlen(stringOne)+1, sizeof(*strOneCopy));
    char* strTwoCopy = calloc(strlen(stringTwo)+1, sizeof(*strTwoCopy));

    strcpy(strOneCopy, stringOne);
    strcpy(strTwoCopy, stringTwo);

    char* strOnePtr = strOneCopy;
    char* strTwoPtr = strTwoCopy;

    int nonOverlapIdx = 0;

    while (*strOnePtr != '\0' && nonOverlapIdx < stringTwoLen) {
        if (*strOnePtr == *strTwoPtr) {
            nonOverlapIdx++;
            strTwoPtr++;
        }
        strOnePtr++;
    }

    char* resString;

    // Case where we do have overlap at certain point prior to end of string two
    if (nonOverlapIdx != 0 && nonOverlapIdx < stringTwoLen) {
        resString = calloc((stringOneLen+stringTwoLen+1), sizeof(*resString));
        strcpy(resString, strOneCopy);
        strcat(resString, strTwoPtr);

        strcpy(array, resString);

        // Case where entirety of string two overlaps with string one
    } else if (nonOverlapIdx != 0 && nonOverlapIdx >= stringTwoLen) {
        resString = calloc(stringOneLen+1, sizeof(*resString));
        strcpy(resString, strOneCopy);

        strcpy(array, resString);

        // Finally, case where there is no overlap
    } else {
        resString = calloc((stringOneLen+stringTwoLen+1), sizeof(*resString));
        strcpy(resString, strOneCopy);
        strcat(resString, strTwoCopy);

        strcpy(array, resString);
    }

    free(strOneCopy);
    free(strTwoCopy);
    free(resString);
}