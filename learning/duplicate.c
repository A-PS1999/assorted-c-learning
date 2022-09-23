#include <stdlib.h>
#include <string.h>

char *duplicate(char str[]) {
    char *copy_str = (char *)malloc(strlen(str)+1); // allocate new pointer to length of string+1

    if (copy_str == NULL) { // if allocation failed
        return NULL; // return null pointer
    }

    strcpy(copy_str, str); // copy input string into new string pointer
    return copy_str;
}