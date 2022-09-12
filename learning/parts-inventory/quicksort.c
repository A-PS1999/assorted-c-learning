#include "quicksort.h"

int split(struct part arr[], int low, int high) {
    struct part part_element = arr[low];

    for (;;) {
        while (low < high && part_element.number <= arr[high].number) {
            high--;
        }
        if (low >= high) break;
        arr[low++] = arr[high];

        while(low < high && arr[low].number <= part_element.number) {
            low++;
        }
        if (low >= high) break;
        arr[high--] = arr[low];
    }
    arr[high] = part_element;
    return high;
}

void quicksort(struct part arr[], int low, int high) {
    int middle;

    if (low >= high) return;
    middle = split(arr, low, high);
    quicksort(arr, low, middle - 1);
    quicksort(arr, middle + 1, high);
}