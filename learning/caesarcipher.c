#include <stdio.h>

#define MAX_MSG_SIZE 80

void encrypt(char *message, int shift);

int main(void)
{
    char ch, message[MAX_MSG_SIZE] = {0};
    int i, shift;

    printf("Please enter a message to encrypt: ");
    for (i=0; (ch = getchar()) != '\n' && i < MAX_MSG_SIZE; i++) {
        message[i] = ch;
    }

    printf("Enter shift amount (1-25): ");
    scanf("%d", &shift);

    while (shift < 1 || shift > 25) {
        printf("Inappropriate input provided. Enter a value between 1-25: ");
        scanf("%d", &shift);
    }

    encrypt(message, shift);
    printf("Your encrypted message: %s", message);

    return 0;
}

void encrypt(char *message, int shift) {

    while (*message) {
        if (*message >= 'A' && *message <= 'Z') {
            *message = ((*message - 'A') + shift) % 26 + 'A';
        } else if (*message >= 'a' && *message <= 'z') {
            *message = ((*message - 'a') + shift) % 26 + 'a';
        }
        message++;
    }
}