#include <stdio.h>
#include <stdlib.h>
#include "min-max-heap.h"

struct minmax_heap* init_minmax_heap() {
    struct minmax_heap *heap;

    if ((heap = calloc(1, sizeof(struct minmax_heap))) == NULL) {
        printf("Error: failed to allocate memory for min-max heap\n");
        exit(EXIT_FAILURE);
    }

    if ((heap = calloc(DEFAULT_HEAP_SIZE, sizeof(int))) == NULL) {
        printf("Error: failed to allocate memory for min-max heap array\n");
        exit(EXIT_FAILURE);
    }

    heap->count = 0;
    heap->size = DEFAULT_HEAP_SIZE;

    return heap;
}