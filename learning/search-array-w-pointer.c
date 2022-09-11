#include <stdbool.h>

bool search(const int arr[], int len, int key)
{
    int *p;

    for (p = arr; p < arr + len; p++) {
        if (*p == key) {
            return true;
        }
        return false;
    }
}