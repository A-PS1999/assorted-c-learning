#include <stdio.h>

int main(void) {
    int test = 1;

    if (*(char *)&test == 1) {
        printf("System is little endian\n");
    } else {
        printf("System is big endian\n");
    }

    return 0;
}