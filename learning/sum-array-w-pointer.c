int sum_array(int arr, int n)
{
    int sum, *p;
    sum = 0;

    for (p = arr; p < arr + n; p++) {
        sum += *p;
    }
    
    return sum;
}