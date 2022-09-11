#include <stdio.h>

void selection_sort(int array[], int length);

int main(void)
{
    int i, ch, length = 0, array[100];

    printf("Please input a list of integers to sort: ");
    for (i=0; i < 100; i++) {
        scanf("%d", &array[i]);
        length++;
        if ((ch = getchar()) == '\n') {
            break;
        }
        ungetc(ch, stdin); // puts non-\n char back to be re-read
    }

    selection_sort(array, length);

    printf("Sorted list: ");
    for (i=0; i < length; i++) {
        printf("%d ", array[i]);
    }

    return 0;
}

void selection_sort(int array[], int length) {
    if (length == 0) {
        return;
    }

    int i, temp, largest=0;

    for (i=0; i < length; i++) {
        if (array[i] > array[largest]) {
            largest = i;
        }
    }

    temp = array[largest];
    array[largest] = array[length-1];
    array[length-1] = temp;

    selection_sort(array, length-1);
}