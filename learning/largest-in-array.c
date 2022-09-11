#include <stdio.h>

int *find_largest(int a[], int n) {
    int i, *largest = &a[0];

    for (i=1; i < n; i++) {
        if (a[i] > *largest) {
            *largest = a[i];
        }
    }
    return largest;
}

int main(void)
{
    int length, i;

    printf("How many numbers do you want in the array?:\n");
    scanf("%d", &length);

    int array[length];

    printf("Enter numbers for your array:\n");
    for (i=0; i < length; i++) {
        scanf("%d", &array[i]);
    }

    printf("The largest element in your array is %d.", *find_largest(array, length));

    return 0;
}