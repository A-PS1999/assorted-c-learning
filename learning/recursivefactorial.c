#include <stdio.h>

int factorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main(void) {
    int n;

    printf("Enter a number and its factorial will be returned: ");
    scanf("%d", &n);

    printf("\nThe factorial of %d is %d", n, factorial(n));

    return 0;
}