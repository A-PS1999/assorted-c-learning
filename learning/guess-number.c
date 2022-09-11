#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMBER 100

void initialize_number_generator(void);
int choose_secret_number(void);
void read_guesses(int secret_number);

int main(void)
{
    char command;
    int secret_number;

    printf("Guess the secret number between 1 and %d.\n", MAX_NUMBER);

    do {
        secret_number = choose_secret_number();
        printf("I picked a new number for you to guess.\n");
        read_guesses(secret_number);
        printf("Play again? ");
        scanf(" %c", &command);
        printf('\n');
    } while (command == 'Y' || command == 'y');

    return 0;
}

void initialize_number_generator(void) {
    srand((unsigned) time(NULL));
}

int choose_secret_number(void) {
    return rand() % MAX_NUMBER + 1;
}

void read_guesses(int secret_number) {
    int guess, num_guesses = 0;

    for (;;) {
        num_guesses++;
        printf("Enter your guess: ");
        scanf(" %d", &guess);

        if (guess == secret_number) {
            printf("You won! It took you %d guesses.\n", num_guesses);
            return;
        } else if (guess < secret_number) {
            printf("Too low, try again.\n");
        } else {
            printf("Too high, try again.\n");
        }
    }
}