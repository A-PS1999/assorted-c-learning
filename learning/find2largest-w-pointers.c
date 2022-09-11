void find_two_largest(const int *a, int len, int *largest, int *second_largest)
{
    int *p = a;
    *largest = *second_largest = *a;

    while (p < a + len) {
        
        if (*p > *largest) {
            *second_largest = *largest;
            *largest = *p;
        } else if (*p > *second_largest) {
            *second_largest = *p;
        }
    }
}