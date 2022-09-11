#include <stdio.h>

int main(void)
{
    int i, n;

    printf("Enter how many numbers you'd like to reverse: ");
    scanf("%d", &n);

    int a[n]; // variable length array decided during runtime

    printf("Enter %d numbers: ", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    printf("Your numbers in reverse are:");
    for (i = n - 1; i >= 0; i--) {
        printf(" %d", a[i]);
    }
    printf("\n");

    return 0;
}