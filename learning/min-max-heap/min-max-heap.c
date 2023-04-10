#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "min-max-heap.h"

static void swap(struct minmax_heap *heap, int i, int j) {
    int temp = heap->data[i];
    heap->data[i] = heap->data[j];
    heap->data[j] = temp;
}

inline int get_first_child_index(int parent_index) {
    return (2*parent_index)+1;
}

inline int get_parent_index(int child_index) {
    return (child_index-1)/2;
}

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

struct minmax_heap* init_minmax_heap_w_custom_size(int size) {
    struct minmax_heap *heap;

    if (size < 0) {
        printf("Error: cannot initialise a heap of negative size, setting size to default\n");
        size = DEFAULT_HEAP_SIZE;
    }

    if ((heap = calloc(1, sizeof(struct minmax_heap))) == NULL) {
        printf("Error: failed to allocate memory for min-max heap\n");
        exit(EXIT_FAILURE);
    }

    if ((heap = calloc(size, sizeof(int))) == NULL) {
        printf("Error: failed to allocate memory for min-max heap array\n");
        exit(EXIT_FAILURE);
    }

    heap->count = 0;
    heap->size = size;

    return heap;
}

void minmax_heap_free(struct minmax_heap* to_free) {
    free(to_free->data);
    free(to_free);
}