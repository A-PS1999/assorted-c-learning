int main(void)
{
    int temperatures[7][24];

    int i, *p;
    i = 0;

    for (p = temperatures[i]; p < temperatures[i] + 24; p++) {
        printf("%d", *p);
    }

    return 0;
}