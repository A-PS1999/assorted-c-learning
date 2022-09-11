#include <stdio.h>

int main(void)
{
    char ch, terminating_char, sentence[200] = {0};
    int i, j, word_length = 0, sentence_length = 0;

    printf("Enter a sentence and it will be reversed: ");

    for (i = 0; (ch = getchar()) != '\n' && i < 200; i++) {
        if (ch == '.' || ch == '?' || ch == '!') {
            terminating_char = ch;
            break;
        } else {
            sentence[i] = ch;
            sentence_length++;
        }
    }

    for (i = sentence_length - 1; i >= 0; i--) {
        if (sentence[i] == ' ' || i == 0) {

            if (i == 0) {
                i--;
            }

            for (j = i + 1; j <= i + word_length + 1; j++) {
                printf("%c", sentence[j]);
            }

            word_length = 0;
        } else {
            word_length++;
        }
    }
    printf("%c", terminating_char);

    return 0;
}