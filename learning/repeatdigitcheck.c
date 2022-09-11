#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    bool digit_seen[10] = {false};
    int digit;
    long n;

    printf("Please enter a number: ");
    scanf("%ld", &n);

    while (n > 0) {
        digit = n % 10;
        if (digit_seen[digit]) {
            break;
        }
        digit_seen[digit] = true;
        n /= 10;
    }

    if (n > 0) {
        printf("The number contains repeated digits\n");
    } else {
        printf("There were no repeated digits in the number\n");
    }

    return 0;
}