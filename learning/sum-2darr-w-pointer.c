#define LEN 10

int sum_two_dimensional_array(int arr[][LEN], int len)
{
    int sum, *p;
    sum = 0;

    for (p = arr; p < arr + len * LEN; p++) {
        sum += *p;
    }

    return sum;
}