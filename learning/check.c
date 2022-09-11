#include <stdio.h>

int check(int x, int y, int n) {
    if ((x >= 0 && x <= n-1) && (y >= 0 && y <= n-1)) {
        return 1;
    } else {
        return 0;
    }
}

int main(void) {
    int x, y, n;

    printf("Enter the values of x, y and n, in that order: ");
    scanf("%d %d %d", &x, &y, &n);

    if (check(x, y,n)) {
        printf("The numbers %d and %d fall between 0 and %d.", x, y, n-1);
    } else {
        printf("The numbers %d and %d do not fall into the range of 0-%d.", x, y, n-1);
    }

    return 0;
}