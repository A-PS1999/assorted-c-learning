#include <stdio.h>
#include <stdlib.h>
#include "stack-non-ADT.h"

struct node {
    int data;
    struct node *next;
};

static struct node *top = NULL;

static void terminate(const char *message) {
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

void make_empty(void) {
    while (!is_empty) {
        pop();
    }
}

bool is_empty(void) {
    return top == NULL;
}

bool is_full(void) {
    // this is because, unlike an array, the linked list theoretically is never full unless
    // we run out of or otherwise cannot allocate memory
    return false;
}

void push(int i) {
    struct node *new_node = malloc(sizeof(struct node));
    if (new_node == NULL) {
        terminate("Error: failed to allocate memory for new node");
    }
    new_node->data = i;
    new_node->next = top;
    top = new_node;
}

int pop(void) {
    struct node *old_top;
    int val_to_return;

    if (is_empty()) {
        terminate("Error: stack is empty");
    }

    old_top = top;
    val_to_return = top->data;
    top = top->next;
    free(old_top);
    return val_to_return;
}