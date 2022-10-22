#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE *input;
    char curr_line[255];
    char *split_str[3];
    int i = 0;
    char *curr_token;

    if (argc != 2) {
        printf("Usage: items-from-file filename\n");
        exit(EXIT_FAILURE);
    }

    if ((input = fopen(argv[1], "r")) == NULL) {
        printf("Error: failed to open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    printf("Item     Unit Price     Purchase Date\n");

    while (fgets(curr_line, sizeof(curr_line), input)) {
        curr_token = strtok(curr_line, ",");

        while (curr_token != NULL) {
            split_str[i++] = curr_token;
            curr_token = strtok(NULL, ",");
        }
        i = 0;

        printf("%d %5c%.2f         %s", atoi(split_str[0]), '$', strtod(split_str[1], NULL), split_str[2]);
    }

    fclose(input);
    return 0;
}