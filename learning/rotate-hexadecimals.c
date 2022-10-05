#include <stdio.h>

unsigned int rotate_left(unsigned int num, int shift);
unsigned int rotate_right(unsigned int num, int shift);

int bitWidth = sizeof(unsigned int) * 8;

int main(void)
{
    unsigned int input;
    int shift_amount;

    printf("Please enter a hexidecimal number: ");
    scanf("%x", &input);

    printf("How many bits would you like to shift the number by? ");
    scanf(" %d", &shift_amount);

    printf("Input rotated %d bits to the left: %x\n", shift_amount, rotate_left(input, shift_amount));
    printf("Input rotated %d bits to the right: %x\n", shift_amount, rotate_right(input, shift_amount));

    return 0;
}

unsigned int rotate_left(unsigned int num, int shift) {
    unsigned int temp = num;

    // shift input number to left by specified amount
    num = num << (shift % bitWidth);

    // shift input number to right such that temp is numbers that were shifted off
    temp = temp >> (bitWidth - (shift % bitWidth));

    // return join of left shift with numbers that were shifted off
    return num | temp;
}

unsigned int rotate_right(unsigned int num, int shift) {
    unsigned int temp = num;

    // shift input number to right by specified amount
    num = num >> (shift % bitWidth);

    temp = temp << (bitWidth - (shift % bitWidth));

    return num | temp;
}