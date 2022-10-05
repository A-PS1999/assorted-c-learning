#include <stdio.h>

// bit fields must be in this order in struct for it to work
// this is implementation-specific (gcc)
struct floating_point {
    unsigned int fraction : 23;
    unsigned int exponent : 8;
    unsigned int sign : 1;
};

union val32 {
    float val;
    struct floating_point fp;
};

int main(void)
{
    union val32 result;
    result.fp.sign = 1;
    result.fp.exponent = 128;
    result.fp.fraction = 0;

    // prints -2.000000
    printf("%f", result.val);

    return 0;
}