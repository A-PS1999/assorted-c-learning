#include <stdio.h>
#include <assert.h>
#include <ctype.h>

#define NUMERAL_TABLE_LEN 7

typedef struct Numeral {
    int value;
    char numeral;
} Numeral;

Numeral numeralTable[NUMERAL_TABLE_LEN] = {
    { 1, 'I' },
    { 5, 'V' },
    { 10, 'X' },
    { 50, 'L' },
    { 100, 'C' },
    { 500, 'D' },
    { 1000, 'M' }
};

int numeralToInt(char* input);
int getNumeralValue(char numeral);

int main(void) {

    assert(numeralToInt("MDCCXXXII") == 1732);
    assert(numeralToInt("MCMXCIX") == 1999);
    assert(numeralToInt("MCMLXVII") == 1967);
    assert(numeralToInt("MCDXCI") == 1491);

    printf("All test cases passed!\n");
   
    return 0;
}

int numeralToInt(char* input) {

    int res = 0;
    char* currNumeral = input;

    while (*currNumeral != '\0') {
        currNumeral++;
    }
    currNumeral--;

    while (isalpha(*currNumeral)) {
        int currNumeralValue = getNumeralValue(*currNumeral);

        /*
            This trick can be used if we iterate backwards based on fact that from right to left,
            numerals trend bigger. Multiplication by 4 is used as the numerals generally increase by multiples of 5+.
            If we find that 4 * the value of the current numeral is smaller than our current sum,
            we know (given how Roman numerals work) that we want to subtract its value from the sum.
        */
        if (4 * currNumeralValue < res) {
            res -= currNumeralValue;
        } else {
            res += currNumeralValue;
        }

        currNumeral--;
    }

    return res;
}

int getNumeralValue(char numeral) {
    for (int i=0; i < NUMERAL_TABLE_LEN; i++) {
        if (numeralTable[i].numeral == numeral) {
            return numeralTable[i].value;
        }
    }
}