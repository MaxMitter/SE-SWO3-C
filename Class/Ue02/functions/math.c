#include "math.h"
#include <stdio.h>

double twice (double x) {
    return 2*x;
}

int main () {
    printf("twice(17)=%f\n", twice(17));

    return 0;
}