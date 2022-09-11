#include <ctype.h>

int read_line(char str[], int n) {
    int ch, i = 0;

    while ((ch = getchar()) != '\n') {
        if (i < n) {
            str[i++] = ch;
        }
    }
    str[i] = '\0';
    return i;
}

int read_line_skip_whitespace(char str[], int n) {
    int ch, i = 0;

    while ((ch = getchar()) != '\n') {
        if (isspace(ch)) {
            ;
        }
        if (i < n) {
            str[i++] = ch;
        }
    }
    str[i] = '\0';
    return i;
}

int read_line_endat_whitespace(char str[], int n) {
    int ch, i = 0;

    while (!isspace(ch = getchar())) {
        if (i < n) {
            str[i++] = ch;
        }
    }
    str[i] = '\0';
    return i;
}

int read_line_newline(char str[], int n) {
    int ch, i = 0;

    while ((ch = getchar()) != '\n') {
        if (ch == '\n' && i < n-1) {
            str[i++] = '\n';
        }
    }
    str[i] = '\0';
    return i;
}