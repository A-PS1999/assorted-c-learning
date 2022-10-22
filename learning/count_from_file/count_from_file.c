#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
    FILE *fp;
    int letter_count = 0;
    int word_count = 0;
    int line_count = 0;
    int ch;

    if (argc != 2) {
        printf("Usage: count_from_file filename\n");
        exit(EXIT_FAILURE);
    }

    if ((fp = fopen(argv[1], "r")) == NULL) {
        printf("Error: failed to open file\n");
        exit(EXIT_FAILURE);
    }

    while ((ch = getc(fp)) != EOF) {
        if (isalpha(ch)) {
            letter_count++;
        }
        if (isspace(ch)) {
            word_count++;
        }
        if (ch == '\n') {
            line_count++;
        }
    }

    fclose(fp);

    printf("Number of letters in file: %d\n", letter_count);
    printf("Number of words in file: %d\n", word_count);
    printf("Number of lines in file: %d\n", line_count);

    return 0;
}