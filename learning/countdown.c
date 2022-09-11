#include <stdio.h>

int main(void)
{
    int i = 10;

    do {
        printf("T minus %d and counting\n", i);
        --i;
    } while (i > 0);

    for (int i2 = 10; i2 > 0; i2--) {
        printf("T minus %d and counting\n", i2);
    }
    
    return 0;
}