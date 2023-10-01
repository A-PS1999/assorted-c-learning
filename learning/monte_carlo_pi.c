#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#define CIRCLE_RADIUS 1
#define NUM_ITERATIONS 10000

double genRandomPoint();
bool pointIsInsideCircle(double x, double y);

int main(void) {

    srand(time(NULL));
    int pointsGenned = 0;
    int pointsInCircle = 0;
    double piApproximation;

    double x, y;

    for (int i=0; i < NUM_ITERATIONS; i++) {
        x = genRandomPoint();
        y = genRandomPoint();

        pointsGenned++;

        if (pointIsInsideCircle(x, y)) {
            pointsInCircle++;
        }

        piApproximation = (double)pointsInCircle / pointsGenned * 4;

        printf("%d points have been generated thus far, with %d of them within the circle.\n", pointsGenned, pointsInCircle);
        printf("From this, pi has been approximated as %g.\n", piApproximation);
        printf("\n");
    }

    return 0;
}

double genRandomPoint() {
    return (double)rand() / (double)RAND_MAX;
}

bool pointIsInsideCircle(double x, double y) {
    return (sqrt((x*x) + (y*y))) < CIRCLE_RADIUS;
}