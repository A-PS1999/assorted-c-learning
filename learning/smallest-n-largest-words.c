#include <stdio.h>
#include <string.h>

#define MAX_WORD_LEN 20

int main(void)
{
    char current_word[MAX_WORD_LEN], 
        largest_word[MAX_WORD_LEN], 
        smallest_word[MAX_WORD_LEN];

    printf("\nEnter word: ");
    scanf("%s", current_word);
    strcpy(smallest_word, strcpy(largest_word, current_word)); // sets all words to scanned input of current_word

    while (strlen(current_word) != 4) {
        printf("\nEnter word: ");
        scanf("%s", current_word);
        if (strcmp(current_word, smallest_word) < 0) { // if current word smaller than current smallest, replace
            strcpy(smallest_word, current_word);
        }
        if (strcmp(current_word, largest_word) > 0) { // if current word larger than current largest, replace
            strcpy(largest_word, current_word);
        }
    }

    printf("Smallest word: %s\n", smallest_word);
    printf("Largest word: %s", largest_word);

    return 0;
}