#ifndef WORD_H
#define WORD_H
#define MAX_WORD_LEN 20

/*
    Reads next word from input and stores it in word. Makes word empty if no word could be read because of EOF.
    Truncates word if word exceeds len. Returns number of chars stored.
*/
int read_word(char *word, int len);

#endif