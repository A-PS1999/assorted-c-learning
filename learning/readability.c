#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAX_TEXT_SIZE 500

int count_letters(char text[]);
int count_words(char text[]);
int count_sentences(char text[]);

int main(void)
{
    char text[MAX_TEXT_SIZE];
    int readingGrade;

    printf("Text: ");
    fgets(text, MAX_TEXT_SIZE, stdin); // get text input from user

    int wordCount = count_words(text);

    // below formula works out reading grade and casts to integer to store in the integer-type readingGrade variable
    readingGrade = round((0.0588 * count_letters(text)/wordCount*100 - 0.296 * count_sentences(text)/wordCount*100 - 15.8));

    if (readingGrade < 1) {
        printf("Before Grade 1");
    } else if (readingGrade > 16) {
        printf("Grade 16+");
    } else {
        printf("Grade %d", readingGrade);
    }

    return 0;
}

int count_letters(char text[]) {
    int letterCount = 0;

    while (*text) {
        if (isalpha((unsigned char)*text)) {
            letterCount++;
        }
        text++;
    }

    return letterCount;
}

int count_words(char text[]) {
    int wordCount = 0;

    while (*text) {
        if (isspace((unsigned char)*text)) {
            wordCount++;
        }
        text++;
    }

    return wordCount;
}

int count_sentences(char text[]) {
    int sentenceCount = 0;

    while (*text) {
        if (*text == '.' || *text == '!' || *text == '?') {
            sentenceCount++;
        }
        text++;
    }

    return sentenceCount;
}