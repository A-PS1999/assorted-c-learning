void find_two_largest(int a[], int n, int *largest, int *second_largest)
{
    int i;

    *largest = a[0];
    *second_largest = a[1];

    for (i=1; i < n; i++) {
        if (a[i] > *largest) {
            *second_largest = *largest;
            *largest = a[i];
        }
        if (a[i] > *second_largest && a[i] != *largest) {
            *second_largest = a[i];
        }
    }
}