#include "helper.h"

int min_of_three(int a, int b, int c) {
    int min = a < b ? a : b;
    return min < c ? min : c;
}

int min_of_two(int a, int b) {
    return a < b ? a : b;
}

int max_of_three(int a, int b, int c) {
    int max = a > b ? a : b;
    return max > c ? max : c;
}