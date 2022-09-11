#include <stdio.h>
#include <ctype.h>

#define MAX_DIGITS 10

void clear_digits_array(void);
void process_digit(int digit, int position);
void print_digits_array(void);

const int segments[10][7] = {{1, 1, 1, 1, 1, 1, 0},
                       {0, 1, 1, 0, 0, 0, 0},
                       {1, 1, 0, 1, 1, 0, 1},
                       {1, 1, 1, 1, 0, 0, 1},
                       {0, 1, 1, 0, 0, 1, 1},
                       {1, 0, 1, 1, 0, 1, 1},
                       {1, 0, 1, 1, 1, 1, 1},
                       {1, 1, 1, 0, 0, 0, 0},
                       {1, 1, 1, 1, 1, 1, 1},
                       {1, 1, 1, 1, 0, 1, 1}};

char digits[4][MAX_DIGITS * 4];

int main(void)
{
    char ch;
    int position = 0;

    clear_digits_array();

    printf("Please enter a number: ");
    while ((ch = getchar()) != '\n') {
        if (isdigit(ch)) {
            process_digit(ch - '0', position);
            position += 4;
        }
    }

    print_digits_array();

    return 0;
}

void clear_digits_array(void) {
    int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < MAX_DIGITS * 4; j++) {
            digits[i][j] = ' ';
        }
    }
}

void process_digit(int digit, int position) {
    digits[0][position + 1] = segments[digit][0] ? '_' : ' ';
    digits[1][position]     = segments[digit][5] ? '|' : ' ';
    digits[1][position + 1] = segments[digit][6] ? '_' : ' ';
    digits[1][position + 2] = segments[digit][1] ? '|' : ' ';
    digits[2][position]     = segments[digit][4] ? '|' : ' ';
    digits[2][position + 1] = segments[digit][3] ? '_' : ' ';
    digits[2][position + 2] = segments[digit][2] ? '|' : ' ';
}

void print_digits_array(void) {
    int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < MAX_DIGITS * 4; j++) {
            putchar(digits[i][j]);
        }
        putchar('\n');
    }
}