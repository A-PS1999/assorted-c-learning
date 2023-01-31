#ifndef MINMAX_HEAP_H
#define MINMAX_HEAP_H

#define DEFAULT_HEAP_SIZE 50

struct minmax_heap {
    unsigned int count;
    unsigned int size;
    int *data;
};

struct minmax_heap* init_minmax_heap();
struct minmax_heap* init_minmax_heap_w_custom_size(unsigned int size);
void minmax_heap_free(struct minmax_heap* to_free);
void minmax_heap_add(struct minmax_heap* heap, int to_add);
int minmax_heap_peek(struct minmax_heap* heap, int min_or_max);
int minmax_heap_pop_min(struct minmax_heap* heap);
int minmax_heap_pop_max(struct minmax_heap* heap);
void minmax_heap_print(struct minmax_heap* heap);

#endif