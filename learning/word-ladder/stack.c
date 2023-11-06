#include "stack.h"

struct Node {
    WordNode data;
    struct Node *next;
};

struct StackType {
    struct Node *top;
    int length;
};

static void terminate(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

Stack create(void) {
    Stack s = malloc(sizeof(struct StackType));
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

void push(Stack s, WordNode node) {
    struct Node *newNode = malloc(sizeof(struct Node));
    if (newNode == NULL) {
        terminate("Error: failed to create a new node");
    }

    newNode->data = node;
    newNode->next = s->top;
    s->length++;
    s->top = newNode;
}

WordNode pop(Stack s) {
    struct Node *oldTop;
    WordNode i;
    
    if (is_empty(s)) {
        terminate("Error: stack is empty");
    }
    
    oldTop = s->top;
    i = oldTop->data;
    s->top = oldTop->next;
    s->length--;
    free(oldTop);
    return i;
}

WordNode peek(Stack s) {
    if (is_empty(s)) {
        terminate("Error: stack is empty");
    }

    return s->top->data;
}

int length(Stack s) {
    return s->length;
}