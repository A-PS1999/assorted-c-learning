#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAX_MSG_LEN 100

bool is_palindrome(char *message);

int main(void)
{
    char message[MAX_MSG_LEN], ch;
    char *p = message;

    printf("Please enter a sentence. This program will check if it is a palindrome: ");
    while ((ch = toupper(getchar())) != '\n' && p < message + MAX_MSG_LEN) {
        if (isalpha(ch))
            *p++ = ch;
    }
    
    if (is_palindrome(message)) {
        printf("Palindrome!");
    } else {
        printf("Not a palindrome.");
    }

    return 0;
}

bool is_palindrome(char *message) {
    char *p, *q;
    p = message;
    int length = strlen(message);

    q = message+length-1;

    while(p < q) {
        if (*p != *q) {
            return false;
        }
        p++;
        q--;
    }

    return true;
}