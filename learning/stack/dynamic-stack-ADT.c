#include <stdio.h>
#include <stdlib.h>
#include "dynamic-stack-ADT.h"

struct stack_type {
    Item *contents; // a dynamic array
    int top;
    int size;
};

static void terminate(const char *message) {
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

Stack create(int size) {
    Stack s = malloc(sizeof(struct stack_type));
    if (s == NULL) {
        terminate("Error: failed to create stack");
    }

    s->contents = malloc(size * sizeof(Item));
    if (s->contents == NULL) {
        free(s);
        terminate("Error: failed to allocate stack array memory");
    }
    s->top = 0;
    s->size = size;

    return s;
}

void destroy(Stack s) {
    free(s->contents);
    free(s);
}

void make_empty(Stack s) {
    s->top = 0;
}

bool is_empty(Stack s) {
    return s->top == 0;
}

bool is_full(Stack s) {
    return s->top == s->size;
}

void push(Stack s, Item i) {
    if (is_full(s)) {
        Stack to_free;

        Stack new_stack = create((s->size)*2);
        new_stack->contents = s->contents;
        new_stack->top = s->top;
        new_stack->contents[new_stack->top++] = i;

        to_free = s;
        s = new_stack;
        destroy(to_free);
    }
    
    s->contents[s->top++] = i;
}

Item pop(Stack s) {
    if (is_empty(s)) {
        terminate("Error: stack is empty");
    }
    return s->contents[--s->top];
} 

Item peek(Stack s) {
    if (is_empty(s)) {
        terminate("Error: stack is empty");
    }

    return s->contents[s->top];
}