#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i, sum = 0;

    for (i=1; i < argc; i++) {
        sum += atoi(argv[i]); // atoi turns string into int
    }
    printf("Total: %d", sum);
    return 0;
}