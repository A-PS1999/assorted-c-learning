#include <stdio.h>

#define MAX_MSG_LEN 80

int main(void) 
{
    char *p, message[MAX_MSG_LEN];

    printf("Enter a message to reverse: ");
    for (p = message; p < message + MAX_MSG_LEN; p++) {
        *p = getchar();
        if (*p == '\n') {
            break;
        }
    }

    printf("The reverse of your message is: ");
    for (p--; p >= &message[0]; p--) {
        putchar(*p);
    }
    putchar('\n');

    return 0;
}