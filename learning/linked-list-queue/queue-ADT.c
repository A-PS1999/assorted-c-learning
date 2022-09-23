#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "queue.h"

struct node {
    Item data;
    struct node *next;
};

// front and back node pointers for keeping track of the front and back of the queue
struct queue_type {
    struct node *front;
    struct node *back;
};

Queue create(void) {
    Queue q = malloc(sizeof(struct queue_type));
    assert(q != NULL && "Error: failed to allocate memory for queue");

    // init both front and back to base NULL state
    q->front = NULL;
    q->back = NULL;

    return q;
}

void destroy(Queue q) {
    // iterate queue, freeing nodes until we get to end of linked list (front becomes NULL)
    while (q->front != NULL) {
        q_remove(q);
    }

    // free now-empty queue
    free(q);
}

void insert(Queue q, Item val) {
    struct node *new_node = malloc(sizeof(struct node));
    assert(new_node != NULL && "Error: failed to allocate memory for new node");
    new_node->data = val;
    new_node->next = NULL;

    // if first entry, front and back can both be set as the newly created node
    if (q->front == NULL && q->back == NULL) {
        q->front = new_node;
        q->back = new_node;
    } else {
        q->back->next = new_node;
        q->back = new_node;
    }
}

void q_remove(Queue q) {
    assert(q->front != NULL && "Error: queue is empty");

    struct node *to_remove;

    to_remove = q->front;

    q->front = q->front->next;

    if (q->front == NULL) {
        q->back = NULL;
    }

    free(to_remove);
}

Item peek_first(Queue q) {
    assert(q->front != NULL && "Error: queue is empty");

    return q->front->data;
}

Item peek_last(Queue q) {
    assert(q->back != NULL && "Error: queue is empty");

    return q->back->data;
}

bool is_empty(Queue q) {
    if (q->front == NULL && q->back == NULL) {
        return true;
    }

    return false;
}