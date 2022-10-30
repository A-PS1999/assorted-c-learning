#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE *infile, *outfile;
    char infile_name[FILENAME_MAX];
    char *outfile_name;
    int shift_amount;
    int curr_char;

    printf("Please enter the name of the file you'd like to encrypt: ");
    fgets(infile_name, FILENAME_MAX, stdin);
    size_t len = strlen(infile_name);

    // fgets stores '\n' which interferes with opening file, so '\n' must be changed to '\0'
    if (infile_name[len-1] == '\n') {
        infile_name[len-1] = '\0';
    }

    if ((infile = fopen(infile_name, "r")) == NULL) {
        printf("Error: failed to open %s", infile_name);
        exit(EXIT_FAILURE);
    }

    printf("Please enter the shift amount for encryption (1-25): ");
    scanf("%d", &shift_amount);

    while (shift_amount < 1 || shift_amount > 25) {
        printf("Inappropriate input provided. Enter a value between 1-25: ");
        scanf("%d", &shift_amount);
    }

    if ((outfile_name = malloc(len+5)) == NULL) {
        perror("Error: failed to allocate memory for output filename\n");
        exit(EXIT_FAILURE);
    }

    strcpy(outfile_name, infile_name);
    strcat(outfile_name, ".enc");

    if ((outfile = fopen(outfile_name, "w")) == NULL) {
        perror("Error: failed to create output file\n");
        exit(EXIT_FAILURE);
    }
    free(outfile_name);

    while ((curr_char = getc(infile)) != EOF) {
        if (curr_char >= 'A' && curr_char <= 'Z') {
            curr_char = ((curr_char - 'A') + shift_amount) % 26 + 'A';
            putc(curr_char, outfile);
        } else if (curr_char >= 'a' && curr_char <= 'z') {
            curr_char = ((curr_char - 'a') + shift_amount) % 26 + 'a';
            putc(curr_char, outfile);
        } else if (curr_char == '\n') {
            putc('\n', outfile);
        } else if (curr_char == ' ') {
            putc(' ', outfile);
        }
    }

    fclose(infile);
    fclose(outfile);

    printf("%s encrypted successfully\n", infile_name);

    return 0;
}