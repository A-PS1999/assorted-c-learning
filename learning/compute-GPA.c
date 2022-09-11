#include <stdio.h>
#include <ctype.h>

float computeGPA(char grades[], int n);

int main(void)
{
    int length, i;

    printf("How many grades would you like to compute a GPA for? Please input an integer: ");
    scanf("%d", &length);

    char grades[length];

    printf("Please input %d grades in this format (B A D B): ", length);
    
    for (i=0; i < length; i++) {
        scanf("%d", &grades[i]);
    }

    printf("The GPA of these grades is: %.1F", computeGPA(grades, length));

    return 0;
}

float computeGPA(char grades[], int n) {
    int j;
    float sum = 0.0F;

    for (j=0; j < n; j++) {
        switch (toupper(grades[j])) {
            case 'A':
                sum += 4.0F;
                break;
            case 'B':
                sum += 3.0F;
                break;
            case 'C':
                sum += 2.0F;
                break;
            case 'D':
                sum += 1.0F;
                break;
            case 'F':
            default:
                break;
        }
    }

    return sum / n;
}