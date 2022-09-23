#include <stdlib.h>

int *create_array(int n, int initial_value) {
    int *arr;
    int i;

    if ((arr = malloc(sizeof(int) * n)) != NULL) {
        for (i=0; i < n; i++) {
            arr[i] = initial_value;
        }

        return arr;
    }

    return NULL;
}