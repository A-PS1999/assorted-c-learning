#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
    FILE *input;
    char firstThree[4], secondThree[4], lastFour[5];
    int num_count = 0;
    int curr_char;

    if (argc != 2) {
        printf("Usage: phone-nos-from-file filename\n");
        exit(EXIT_FAILURE);
    }

    if ((input = fopen(argv[1], "r")) == NULL) {
        perror("Error: failed to open input file\n");
        exit(EXIT_FAILURE);
    }

    while ((curr_char = getc(input)) != EOF) {
        if (isdigit(curr_char) && num_count < 3) {
            firstThree[num_count++] = curr_char;
        }
        if (num_count == 3) {
            firstThree[num_count++] = '\0';
        } 
        else if (isdigit(curr_char) && (num_count > 3 && num_count < 7)) {
            // minus 4 ensures we can fill second array from 0 despite increasing count
            secondThree[num_count++ - 4] = curr_char;
        }
        if (num_count == 7) {
            secondThree[num_count++ - 4] = '\0'; 
        }
        else if (isdigit(curr_char) && (num_count > 7 && num_count < 12)) {
            // minus 8 performs same function as above
            lastFour[num_count++ - 8] = curr_char;
        }
        if (num_count == 12) {
            lastFour[num_count - 8] = '\0';
            printf("(%s) %s-%s\n", firstThree, secondThree, lastFour);
            num_count = 0;
        }
    }

    fclose(input);
    return 0;
}