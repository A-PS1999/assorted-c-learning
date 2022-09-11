#include <stdio.h>

int main(void)
{
    int matrix[5][5];
    int i, j, total;

    for (i=0; i < 5; i++) {
        for (j=0; j < 5; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("Row totals: ");

    for (i=0; i < 5; i++) {
        total = 0;
        for (j=0; j < 5; j++) {
            total += matrix[i][j];
        }
        printf("%d ", total);
    }

    printf("Column totals: ");

    for (i=0; i < 5; i++) {
        total = 0;
        for (j=0; j < 5; j++) {
            total += matrix[j][i];
        }
        printf("%d ", total);
    }

    printf("\n");

    return 0;
}