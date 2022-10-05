#include <stdio.h>

int count_ones(unsigned char ch);

int main(void)
{
    unsigned char input_ch;

    printf("Please enter a character: ");
    scanf(" %c", &input_ch);

    printf("The number of 1-bits in %c is %d", input_ch, count_ones(input_ch));

    return 0;
}

int count_ones(unsigned char ch) {
    int c;

    for (c=0; ch; c++) {
        // &= ch-1 has effect of setting least significant bit of ch to 0, gradually clearing the set (1) bits of ch
        ch &= ch-1;
    }

    return c;
}