#include <stdio.h>
#include "queue.h"

int main(void)
{
    Queue test_queue;

    test_queue = create();

    if (is_empty(test_queue)) {
        printf("The queue is empty\n");
    }

    insert(test_queue, 4);
    printf("The last item in the queue is %d\n", peek_last(test_queue));

    if (!is_empty(test_queue)) {
        printf("The queue is not empty\n");
    }

    insert(test_queue, 6);
    printf("The first item in the queue is %d\n", peek_first(test_queue));
    printf("The last item in the queue is %d\n", peek_last(test_queue));

    insert(test_queue, 9);
    q_remove(test_queue);
    printf("The first item in the queue is %d\n", peek_first(test_queue));

    for (int i=0; i < 2; i++) {
        q_remove(test_queue);
    }

    if (is_empty(test_queue)) {
        printf("The queue is empty again\n");
    }

    destroy(test_queue);

    return 0;
}