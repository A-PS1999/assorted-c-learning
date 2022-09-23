#include <stdio.h>

void *malloc_wrapper(size_t n) {
    void *p;
    if ((p = malloc(n)) == NULL) {
        printf("Error: memory allocation to pointer failed");
        return -1;
    }
    
    return p;
}