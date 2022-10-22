#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE *input, *output;
    char *input_file_ext;
    char *output_filename;
    int count_byte, curr_byte, count;

    if (argc != 2) {
        printf("Usage: uncompress_file filename\n");
        exit(EXIT_FAILURE);
    }

    input_file_ext = strrchr(argv[1], '.');
    int size = strlen(argv[1]);

    if ((strcmp(input_file_ext, ".rle")) != 0) {
        printf("Cannot uncompress a file has not been compressed\n");
        exit(EXIT_FAILURE);
    }

    output_filename = malloc(sizeof(argv[1]));
    strcpy(output_filename, argv[1]);
    // cut off '.rle' from the end of filename, to make sure output filename is same name and file type as what was originally compressed 
    output_filename[size-4] = '\0';

    if ((input = fopen(argv[1], "rb")) == NULL) {
        perror("Error: failed to open file\n");
        exit(EXIT_FAILURE);
    }

    if ((output = fopen(output_filename, "wb")) == NULL) {
        perror("Error: failed to create and open file to write to");
        exit(EXIT_FAILURE);
    }
    free(output_filename);

    while (curr_byte != EOF) {
        count_byte = getc(input);
        curr_byte = getc(input);
        count = 0;

        while (count < count_byte) {
            putc(curr_byte, output);
            count++;
        }
    }

    fclose(input);
    fclose(output);

    printf("File uncompressed successfully\n");

    return 0;
}