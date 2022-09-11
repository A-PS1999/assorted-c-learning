#include <stdio.h>

int main(void)
{
    int i, n;

    printf("Enter the number of square numbers you'd like to generate: ");
    scanf("%d", &n);
    getchar();

    for (i = 1; i <= n; i++) {
        printf("%10d%10d\n", i, i * i);
        if (i % 24 == 0) {
            printf("Press any key to continue...");
            getchar();
        }
    }

    return 0;
}