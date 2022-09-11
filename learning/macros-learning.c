#include <stdio.h>
#define cube(x) (x*x*x)
#define modulo_four(n) (n%4)
#define hundred_sum_check(a, b) (a+b < 100 ? 1 : 0)
#define NELEMS(arr) (sizeof(arr)/sizeof(arr[0]))
#define CHECK(one, two, limit) ((one > 0 && one <= limit-1) && (two > 0 && two <= limit-1) ? 1 : 0)
#define MEDIAN(x, y, z) ((x+y+z)/3)
#define POLYNOMIAL(x) (3*(x*x*x*x*x)+2*(x*x*x*x)-5*(x*x*x)-(x*x)+(7*x)-6)

int main(void)
{
    int x = 2;
    int y = 4;
    int n = 6;
    int a = 51;
    int b = 50;
    int arr[] = {1, 2, 3, 4, 5, 6};

    printf("Cube of %d is %d\n", x, cube(x));
    printf("%d modulo 4 is %d\n", n, modulo_four(n));
    printf("Because %d + %d is greater than 100, result is %d\n", a, b, hundred_sum_check(a, b));
    printf("Array contains %ld elements\n", NELEMS(arr));
    printf("Do %d and %d fall in the range 0-%d? %d\n", x, n, a, CHECK(x, n, a));
    printf("The median of %d, %d and %d is %d\n", x, y, n, MEDIAN(x, y, n));
    printf("The result of the macro parameter of %d is %d\n", y, POLYNOMIAL(y));

    return 0;
}