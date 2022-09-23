#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "queue.h"

struct queue_type {
    Item *array; // dynamically allocated array of items
    int size; // size of array
    int num_items; // number of items currently in array
    int front; // front of queue
    int rear; // rear of queue
};

Queue create(int size) {
    Queue q = malloc(sizeof(struct queue_type)); // allocate memory for queue
    assert(q != NULL && "Error: failed to allocate memory for queue");

    q->array = malloc(size * sizeof(Item)); // allocate memory for queue array, to size parameter
    assert(q->array != NULL && "Error: failed to allocate memory for queue array");
    q->size = size;
    q->front = -1; // initialize front and rear of queue to -1 to indicate empty
    q->rear = -1;
    q->num_items = 0; // 0 to indicate no items

    return q;
}

void destroy(Queue q) {
    free(q->array); // free queue array memory
    free(q); // free queue memory
}

void insert(Queue q, Item val) {
    assert(q->num_items != q->size && "Error: queue is full"); // assert that queue is not full

    if (q->front == -1 && q->rear == -1) { // if first insertion to queue
        q->front++; // increment front to 0, to indicate first element of array
        q->array[++q->rear] = val;
    } else {
        q->array[++q->rear] = val; // increment rear of queue and write val to rear position
    }

    q->num_items++; // increment number of items in queue
}

void q_remove(Queue q) {
    if (q->front == q->size && q->rear == q->size) { // if one remaining value in queue
        q->front = -1; // reset front, rear and num_items to original values
        q->rear = -1;
        q->num_items = 0;
    } else {
        q->front++; // increment front, thus pointing to new 'front' of queue and effectively removing the old front value
    }
}

Item peek_first(Queue q) {
    assert(q->front != -1 && "Error: queue is empty"); // assert that the array has had something inserted
    return q->array[q->front]; // return front value
}

Item peek_last(Queue q) {
    assert(q->rear != -1 && "Error: queue is empty"); // assert that something has been inserted
    return q->array[q->rear]; // return rear value
}

bool is_empty(Queue q) {
    return q->front == -1; // returns true if front is -1. In other words, that queue has been reset or not had any insertion
}