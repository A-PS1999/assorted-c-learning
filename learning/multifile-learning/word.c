#include <stdio.h>
#include "word.h"

int read_char(void) {
    int ch = getchar();

    if (ch == '\n' || ch == '\t') {
        return ' ';
    }

    return ch;
}

int read_word(char *word, int len) {
    int ch, pos = 0;

    while ((ch = read_char()) == ' '); // skip over spaces

    while (ch != ' ' && ch != EOF) { // read char until reaching space or EOF
        if (pos < len) {
            word[pos++] = ch;
        }
        ch = read_char();
    }
    word[pos] = '\0'; // end with null character to create string

    if (pos > MAX_WORD_LEN) { // asterisk to indicate truncated word if it's greater than max word length
        word[MAX_WORD_LEN] = '*';
    }

    return pos;
}