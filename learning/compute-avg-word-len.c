#include <stdio.h>
#include <ctype.h>

#define SENTENCE_LIMIT 80

double compute_average_word_length(const char *sentence);

int main(void)
{
    char sentence[SENTENCE_LIMIT];

    printf("Enter a sentence: ");
    fgets(sentence, SENTENCE_LIMIT, stdin);

    printf("\nThe average length of words in your sentence is %.1f", compute_average_word_length(sentence));

    return 0;
}

double compute_average_word_length(const char *sentence) {

    int words, length;
    words = length = 0;

    while (*sentence) {
        while (*sentence && !isspace((unsigned char)*sentence)) { // increments sentence and length of sentence while ignoring spaces
            sentence++;
            length++;
        }
        words++; // increments number of words once. Words gets incremented after above while loop has executed once

        while (*sentence && isspace((unsigned char)*sentence)) { // This loop increments through spaces until it hits a non-space,
            sentence++;                                          // where the above while loop will re-execute
        }
    }

    return (double) words / length;
}