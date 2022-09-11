#include <stdio.h>

#define MAX_NAME_LEN 30

void reverse_name(char *name);

int main(void)
{
    char name[MAX_NAME_LEN];

    printf("Enter a name: ");
    fgets(name, MAX_NAME_LEN, stdin);

    reverse_name(name); // reverses and prints name

    return 0;
}

void reverse_name(char *name) {
    char *p = name, initial;

    while (*p == ' ') { // skips through any spaces before the name
        p++;
    }
    initial = *p++; // sets initial to first letter of name

    while (*p && *p++ != ' ') { // skips through other letters in first name
        ;
    }

    while (*p && *p != '\n') { // reads second name into stdout, prints it
        putchar(*p++);
    }

    printf(", %c.\n", initial); // prints initial
}