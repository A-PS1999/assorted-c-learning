#include <stdio.h>

#define N 10

int main(void)
{
    int array[N], *p;

    printf("Enter %d numbers: ", N);
    for (p = array; p < array + N; p++) {
        scanf("%d", p);
    }

    printf("Your numbers in reverse order are: ");
    for (p = array+N-1; p >= array; p--) {
        printf(" %d", *p);
    }
    printf("\n");

    return 0;
}