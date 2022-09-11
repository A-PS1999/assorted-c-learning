#include <stdio.h>
#include <ctype.h>

int compute_score(char word[]);

int main(void)
{
    int player1_score;
    int player2_score;
    char word[50];

    printf("Player 1, please input a word: ");
    scanf("%s", word);

    player1_score = compute_score(word);

    printf("Player 2, please input a word: ");
    scanf("%s", word);

    player2_score = compute_score(word);

    if (player1_score == player2_score) {
        printf("Tie!");
    } else if (player1_score > player2_score) {
        printf("Player 1 wins!");
    } else {
        printf("Player 2 wins!");
    }

    return 0;
}

int compute_score(char *word) {
    int points[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int score = 0;

    while (*word) { // continue while word exists
        if isalpha((int)*word) { // if valid letter ((int) needed to cast char to int for isalpha())
            score += points[toupper(*word) - 'A']; // *word - 'A' gets int value of letter e.g. A = 0, so 1 in points array
        }
        word++; // increment word
    }

    return score;
}