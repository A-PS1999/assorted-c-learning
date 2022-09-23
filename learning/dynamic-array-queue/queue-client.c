#include <stdio.h>
#include "queue.h"

int main(void) 
{
    Queue queue1, queue2;

    queue1 = create(10);
    queue2 = create(20);

    for (int i=1; i < 9; i++) {
        insert(queue1, i);
    }
    printf("First item in queue1: %d\n", peek_first(queue1));
    printf("Last item in queue1: %d\n", peek_last(queue1));

    q_remove(queue1);
    printf("First item in queue1: %d\n", peek_first(queue1));

    if (is_empty(queue2)) {
        printf("queue2 is empty\n");
    }

    insert(queue2, 5);
    printf("Last item in queue2: %d\n", peek_last(queue2));

    destroy(queue1);
    destroy(queue2);

    return 0;
}