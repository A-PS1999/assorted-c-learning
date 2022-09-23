#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef int Item;
typedef struct queue_type *Queue;

Queue create(int size);
void destroy(Queue q);
void insert(Queue q, Item val);
void q_remove(Queue q);
Item peek_first(Queue q);
Item peek_last(Queue q);
bool is_empty(Queue q);

#endif