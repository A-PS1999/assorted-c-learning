#include <stdio.h>

int main(void)
{
    int height = 0;

    do {
        printf("Please enter a height number: ");
        scanf("%d", &height);
    } while (height < 1);

    for (int i = 0; i < height; i++) {
        for (int j = i; j < height-1; j++) { // print spaces up to just before height, so that lowest level has no spaces
            printf(" ");
        }

        for (int blockCount = 0; blockCount <= i; blockCount++) { // print blocks equal to each level of tower or i
            printf("#");
        }
        printf("  "); // 2 space between the two block segments
        for (int blockCount = 0; blockCount <= i; blockCount++) {
            printf("#");
        }
        printf("\n"); // new line, for new level of the tower or i
    }

    return 0;
}