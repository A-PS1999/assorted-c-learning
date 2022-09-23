#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LEN 20

int compare_string_len(const void *str1, const void *str2); // needed for qsort function

int main(void) {
    int arr_size = 10;
    int word_count = 0;
    char **words = malloc(sizeof(char *) * 10); // init size of array of pointers
    char *word = NULL; // dynamic string pointer

    do { // while loop executes while input is not a blank string aka just '\n'
        word = malloc(sizeof(char) * MAX_WORD_LEN+1); // allocate size of word

        printf("Enter a word: ");
        fgets(word, MAX_WORD_LEN+1, stdin);

        if (word[0] != '\n') {
            word[strlen(word)-1] = '\0'; // remove '\n' from end of string for formatting purposes
            words[word_count] = word; // add string pointer to array of pointers
            word_count++; // increment word count
        }

        if (word_count == arr_size) { // if max current size of array of pointers reached
            if ((words = realloc(words, sizeof(char *) * (arr_size *= 2))) == NULL) { // attempt realloc to double size
                printf("Error: Array size reallocation failure\n");
                return -1;
            }
        }
    } while (word[0] != '\n');

    qsort(words, word_count, sizeof(char *), compare_string_len); // qsort to sort by length

    printf("In sorted order: ");
    for (int i=0; i < word_count; i++) {
        printf("%s ", words[i]);
    }

    return 0;
}

int compare_string_len(const void *str1, const void *str2) {
    const char* one = *(const char **)str1;
    const char* two = *(const char **)str2;

    if (strlen(one) > strlen(two)) {
        return 1;
    } else if (strlen(two) > strlen(one)) {
        return -1;
    } else return strcmp(one, two);
}