#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define MAX_LINE_LEN 10

int main(int argc, char* argv[])
{
    FILE *fp;
    unsigned char file_line[MAX_LINE_LEN];
    int offset = 0;
    int file_bytes;

    if (argc != 2) {
        printf("Usage: file_as_bytes filename\n");
        exit(EXIT_FAILURE);
    }

    if ((fp = fopen(argv[1], "rb")) == NULL) {
        perror("Error: failed to open file");
        exit(EXIT_FAILURE);
    }

    printf("Offset               Bytes              Characters\n");
    printf("------  ------------------------------  ----------\n");

    // continually read 10 byte lines into array and operate on them
    // until 0 bytes are returned (file has been read completely)
    while ((file_bytes = fread(file_line, sizeof(unsigned char), 10, fp)) > 0) {
        printf("%6d   ", offset);

        // print the 10 bytes from the array
        for (size_t i=0; i < (sizeof(file_line)/sizeof(file_line[0])); i++) {
            printf("%-3.2X", file_line[i]);
        }
        printf("  ");
        
        // print the printable characters from the current line
        for (int i=0; i < file_bytes; i++) {
            printf("%c", isprint(file_line[i]) ? file_line[i] : '.');
        }
        printf("\n");

        // increase offset for the next line
        offset += 10;
    }

    fclose(fp);
    return 0;
}