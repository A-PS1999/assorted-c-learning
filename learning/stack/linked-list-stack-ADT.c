#include <stdio.h>
#include <stdlib.h>
#include "linked-list-stack-ADT.h"

struct node {
    Item data;
    struct node *next;
};

struct stack_type {
    struct node *top;
    int length;
};

static void terminate(const char *message) {
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

Stack create(void) {
    Stack s = malloc(sizeof(struct stack_type));
    if (s == NULL) {
        terminate("Error: failed to create stack");
    }
    s->top = NULL;
    s->length = 0;

    return s;
}

void destroy(Stack s) {
    make_empty(s);
    free(s);
}

void make_empty(Stack s) {
    while (!is_empty(s)) {
        pop(s);
    }
}

bool is_empty(Stack s) {
    return s->top == NULL;
}

bool is_full(Stack s) {
    return false;
}

void push(Stack s, Item i) {
    struct node *new_node = malloc(sizeof(struct node));
    if (new_node == NULL) {
        terminate("Error: failed to create a new node");
    }

    new_node->data = i;
    new_node->next = s->top;
    s->length++;
    s->top = new_node;
}

Item pop(Stack s) {
    struct node *old_top;
    Item i;
    
    if (is_empty(s)) {
        terminate("Error: stack is empty");
    }
    
    old_top = s->top;
    i = old_top->data;
    s->top = old_top->next;
    s->length--;
    free(old_top);
    return i;
}

Item peek(Stack s) {
    if (is_empty(s)) {
        terminate("Error: stack is empty");
    }

    return s->top->data;
}

int length(Stack s) {
    return s->length;
}