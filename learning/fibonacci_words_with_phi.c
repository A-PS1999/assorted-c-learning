#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define PHI 1.6180339887498948482045868343656

bool fibword_phi(int n);

int main(void) {

    char buffer[10];
    int n;

    printf("Please enter an integer n: ");

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        sscanf(buffer, "%d", &n);
    }

    bool ret = fibword_phi(n);

    printf("The %dth digit of the Fibonacci word sequence is %d.\n", ret);

    return 0;
}

bool fibword_phi(int n) {
    return (2+floor((n*PHI))-floor(((n+1)*PHI)));
}