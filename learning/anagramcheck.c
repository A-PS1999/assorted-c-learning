#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_WORD_LEN 30

bool are_anagrams(const char *word1, const char *word2);

int main(void)
{
    char word1[MAX_WORD_LEN];
    char word2[MAX_WORD_LEN];

    printf("Enter the first word you'd like to compare: ");
    fgets(word1, MAX_WORD_LEN, stdin);

    printf("Enter the second word you'd like to compare: ");
    fgets(word2, MAX_WORD_LEN, stdin);

    if (are_anagrams(word1, word2)) {
        printf("%s and %s are anagrams!", word1, word2);
    } else {
        printf("%s and %s are not anagrams.", word1, word2);
    }

    return 0;
}

bool are_anagrams(const char *word1, const char *word2) {
    bool are_anagrams = true;
    int alphabet_count[26] = {0};

    while (*word1) {
        alphabet_count[toupper(*word1) - 'A']++;
        word1++;
    }

    while (*word2) {
        alphabet_count[toupper(*word2) - 'A']--;
        word2++;
    }

    for (int i = 0; i < 26; i++) {
        if (alphabet_count[i] != 0) {
            are_anagrams = false;
            break;
        }
    }

    return are_anagrams;
}