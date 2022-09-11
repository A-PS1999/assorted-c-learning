#include <stdio.h>
#include <math.h>

int polynomial_result(int x) {
    return (3 * pow((double)x, (double)5) + 
        (2 * pow((double)x, (double)4)) -
        (5 * pow((double)x, (double)3)) -
        (x * x) +
        (7 * pow((double)x, (double)7)) - 6
    );
}

int main(void)
{
    int x;

    printf("Please enter a value for x: ");
    scanf("%d", &x);

    printf("The result of the polynomial calculation is: %d", polynomial_result(x));

    return 0;
}