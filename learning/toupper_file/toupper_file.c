#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
    FILE *fp;
    char file_str[200];

    if (argc != 2) {
        printf("Usage: toupper_file filename\n");
        exit(EXIT_FAILURE);
    }

    if ((fp = fopen(argv[1], "r")) == NULL) {
        perror("Error: failed to open file\n");
        exit(EXIT_FAILURE);
    }

    if ((fgets(file_str, 200, fp)) == NULL) {
        perror("Error: failed to read from file\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i=0; i < (sizeof(file_str)/sizeof(file_str[0])); i++) {
        if (isalpha((unsigned char)file_str[i])) {
            file_str[i] = toupper((unsigned char)file_str[i]);
        }
    }

    printf("%s", file_str);

    fclose(fp);
    return 0;
}