#include <stdio.h>

void swap(int *p, int *q);

int main(void)
{
    int i, j;

    printf("Please input the values of i and j. Please enter i, followed by a space, then j.\n");
    scanf("%d %d", &i, &j);

    printf("The current values of i and j are %d and %d respectively", i, j);

    swap(&i, &j);

    printf("Having been swapped, i and j are now %d and %d respectively", i, j);

    return 0;
}

void swap(int *p, int *q) {
    int temp;

    temp = *p;
    *p = *q;
    *q = temp;
}