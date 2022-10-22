#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    FILE *fp;

    if (argc < 2) {
        printf("Usage: fcat filename(s)\n");
        exit(EXIT_FAILURE);
    }

    for (int i=1; i < argc; i++) {
        int ch;

        if ((fp = fopen(argv[i], "r")) == NULL) {
            perror("Error: failed to open file");
            exit(EXIT_FAILURE);
        }

        while ((ch = getc(fp)) != EOF) {
            putchar(ch);
        }

        fclose(fp);
    }

    return 0;
}