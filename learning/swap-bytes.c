#include <stdio.h>

unsigned short swap_bytes(unsigned short num);

int main(void)
{
    unsigned short input;

    printf("Please enter a number (up to four digits): ");
    scanf("%hx", &input);

    unsigned short output = swap_bytes(input);

    printf("Number with bytes swapped: %hx", output);

    return 0;
}

unsigned short swap_bytes(unsigned short num) {
    // shifting by 8 bits in either direction allows us to get the left and right bytes on their own, and in a swapped position
    // such that the effect of OR (|) is effectively the same as joining them together again.
    return (num << 8) | (num >> 8);
}