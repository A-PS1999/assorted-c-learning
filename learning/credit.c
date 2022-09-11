#include <stdio.h>
#include <stdbool.h>

bool check_number_len(int len, long card_number) {
    long temp_num = card_number;

    do {
        temp_num /= 10; // decrement length of number by dividing by 10, cutting off last digit
        len++; // increment length variable
    } while (temp_num > 0);

    if (len != 13 && len != 15 && len != 16) { // if number length not 13, 15 or 16
        return false;
    }

    return true;
}

int main(void)
{
    long card_number;
    int len = 0;
    int sum = 0;

    printf("Please input a credit card number: ");
    scanf("%ld", &card_number);

    long card_number_backup = card_number;

    if (!check_number_len(len, card_number)) { // check that card number is appropriate length
        printf("INVALID\n");
        return 0;
    }

    for (int i = len; i > 0; i--) { // decrement through length of number
        int current_digit = card_number % 10; // the last number in the array e.g. 408 % 10 = 8
        if (i % 2 == 0) { // if current position in length is even e.g. every other number
            sum += current_digit;
        } else { // case for 1st, 3rd, 5th, etc number
            sum += (current_digit*2);
        }

        card_number = card_number / 10; // shorten number to cut off last digit, allow for next loop to get new last digit
    }

    if (sum % 10 != 0) { // condition for valid credit card
        printf("INVALID\n");
        return 0;
    }

    do {
        card_number_backup /= 10;
    } while(card_number_backup > 100); // cuts card number down to first 2 digits

    if (card_number_backup == 34 || card_number_backup == 37) { // criteria for Amex
        printf("AMEX\n");
    } else if (card_number_backup >= 51 && card_number_backup <= 55) { // criteria for MasterCard
        printf("MASTERCARD\n");
    } else if (card_number_backup/10 == 4) { // criteria for Visa
        printf("VISA\n");
    } else {
        printf("INVALID\n");
    }

    return 0;
}