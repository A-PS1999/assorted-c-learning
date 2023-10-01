#include <stdio.h>
#include <stdbool.h>
#include <float.h>
#include <math.h>

#define PI_TO_7_DP 3.1415926

bool isBasicallyIdentical(double a);

int main(void) {

    bool shouldSubtract = true;
    double piApproximation = 4.0;
    int oddNumber = 3.0;
    int numIterations = 0;

    while (!isBasicallyIdentical(piApproximation)) {
        if (shouldSubtract) {
            piApproximation -= (4.0/oddNumber);
        } else {
            piApproximation += (4.0/oddNumber);
        }

        oddNumber += 2.0;
        numIterations++;
        shouldSubtract = !shouldSubtract;
    }

    printf("It took %d iterations to approximate pi to 7 decimal places.\n", numIterations);

    return 0;
}

bool isBasicallyIdentical(double a) {
    return (fabs(a-PI_TO_7_DP) < (DBL_EPSILON * fabs(a + PI_TO_7_DP)));
}