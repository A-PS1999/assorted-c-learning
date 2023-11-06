#ifndef STACK_ADT_H
#define STACK_ADT_H

#include "word-ladder.h"

typedef struct StackType *Stack;

Stack create(void);
void destroy(Stack s);
void make_empty(Stack s);
bool is_empty(Stack s);
bool is_full(Stack s);
void push(Stack s, WordNode i);
WordNode pop(Stack s);
WordNode peek(Stack s);
int length(Stack s);

#endif
