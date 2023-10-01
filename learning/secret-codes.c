#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_MSG_LEN 1000

int scode(int a);

int main(void) {

    char buffer[MAX_MSG_LEN] = {0};
    char ch;

    printf("Enter a message, and this program will encrypt it into a secret coded message: ");

    for (int i=0; (ch = getchar()) != '\n' && i < MAX_MSG_LEN; i++) {
        ch = scode(ch);
        buffer[i] = ch;
    }

    printf("Your secret message is: %s\n", buffer);

    return 0;
}

int scode(int a) {
    if (!isalpha(a)) {
        return a;
    } else if (isalpha(a) && isupper(a)) {
        return 'Z' - a + 'A';
    } else {
        return 'z' - a + 'a';
    }
}