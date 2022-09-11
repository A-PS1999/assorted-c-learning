#include <stdio.h>
#include <ctype.h>

int compute_vowel_count(const char *sentence);

int main(void) {

    char sentence[30];
    char ch, *p = sentence;

    printf("Enter a sentence and its vowels will be counted: ");
    while ((ch = getchar()) != '\n' && p < sentence + 30) {
        *p++ = ch;
    }
    p = '\0';

    printf("\nYou have %d vowel(s) in your sentence.", compute_vowel_count(sentence));

    return 0;
}

int compute_vowel_count(const char *sentence) {
    int count = 0;

    while (*sentence) {
        switch (toupper(*sentence++)) {
            case 'A': case 'E': case 'I': case 'O': case 'U':
                count++; break;
            default:
                break; 
        }
    }

    return count;
}