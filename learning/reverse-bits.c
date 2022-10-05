#include <stdio.h>

unsigned int reverse_bits(unsigned int num);

int main(void)
{
    unsigned input;

    printf("Please enter a non-negative integer: ");
    scanf("%u", &input);

    printf("As entered, the hexadecimal representation of %u is %x\n", input, input);
    printf("After reversing the bits, %u now has the hexadecimal representation %x, %u in decimal", input, reverse_bits(input), reverse_bits(input));

    return 0;
}

unsigned int reverse_bits(unsigned int num) {
    unsigned result = 0;

    while (num) {
        // shift result left by one per iteration, to fill in bits and avoid overwrites
        result <<= 1;
        // |= (num&1) has effect of adding last significant bit to result if it is a 1, 0 otherwise
        result |= (num & 1);
        // shift num right by one to change what least significant bit is, and gradually clear num as part of loop condition
        num >>= 1;
    }

    return result;
}