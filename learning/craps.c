#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int roll_dice(void);
bool play_game(void);

int main(void)
{
    int wins = 0, losses = 0;
    char ch;

    srand((unsigned) time(NULL));

    while (true) {
        if (play_game()) {
            printf("You won!\n");
            wins++;
        } else {
            printf("You lose!\n");
            losses++;
        }

        printf("Would you like to play again? ");
        scanf(" %c", &ch);

        if (ch != 'Y' && ch != 'y') {
            break;
        }
        printf("\n");
    }

    printf("Wins: %d\nLosses: %d", wins, losses);

    return 0;
}

int roll_dice(void) {
    return (rand() % 6 + rand() % 6) + 2;
}

bool play_game(void) {
    int roll;
    int point = 0;

    while (true) {
        roll = roll_dice();
        printf("You rolled %d\n", roll);

        if (point == 0) {
            switch(roll) {
				case 7: 
				case 11: return true;
				case 2:
				case 3:
				case 12: return false;
				default: point = roll; printf("The point is %d\n", point);
			}
        } else {
            if (roll == point) {
                return true;
            }
            else if (roll == 7) {
                return false;
            }
        }
    }
}