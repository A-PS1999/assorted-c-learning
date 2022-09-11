double inner_product(const double *a, const double *b, int len)
{
    double product;
    int i = 0;

    while (i++ < len) {
        product += (*a++ * *b++);
    }

    return product;
}