#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int fibonnaci_numbers[40] = {0, 1};
    int i;

    printf("The first 40 fibonnaci numbers:\n");
    printf("%d\n", fibonnaci_numbers[0]);
    printf("%d\n", fibonnaci_numbers[1]);
    for (i = 2; i < 40; i++) {
        int sum = fibonnaci_numbers[i-1] + fibonnaci_numbers[i-2];
        fibonnaci_numbers[i] = sum;
        printf("%d\n", fibonnaci_numbers[i]);
    }

    return 0;
}