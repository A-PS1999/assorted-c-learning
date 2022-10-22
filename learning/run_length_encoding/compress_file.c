#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE *to_compress, *output;
    char *input_file_ext;
    int byte, next_byte, same_byte_count;

    if (argc != 2) {
        printf("Usage: compress_file filename\n");
        exit(EXIT_FAILURE);
    }

    input_file_ext = strrchr(argv[1], '.');
    char *output_filename = malloc(sizeof(argv[1])+5);

    if ((strcmp(input_file_ext, ".rle")) == 0) {
        printf("Cannot compress a file which has already been compressed\n");
        exit(EXIT_FAILURE);
    }

    if ((to_compress = fopen(argv[1], "rb")) == NULL) {
        perror("Error: failed to open file\n");
        exit(EXIT_FAILURE);
    }

    strcpy(output_filename, argv[1]);
    strcat(output_filename, ".rle");

    if ((output = fopen(output_filename, "wb")) == NULL) {
        perror("Error: failed to create and open file to write to");
        exit(EXIT_FAILURE);
    }
    free(output_filename);

    // initialize both byte pointers to same initial byte. This helps ensure that same_byte_count will always be at least 1
    byte = getc(to_compress);
    next_byte = byte;
    while (next_byte != EOF) {
        // increment count and move next_byte along for as long as byte and next_byte are the same (and count less than 255 overall)
        for (same_byte_count=0; next_byte == byte && same_byte_count < 255; same_byte_count++) {
            next_byte = getc(to_compress);
        }
        // write count byte to output file
        putc(same_byte_count, output);
        // then write byte to output file
        putc(byte, output);
        // move first byte pointer along to next_byte (has effectively same effect as the initial byte pointer initialisation)
        byte = next_byte;
    }

    fclose(to_compress);
    fclose(output);

    printf("File compressed successfully\n");

    return 0;
}