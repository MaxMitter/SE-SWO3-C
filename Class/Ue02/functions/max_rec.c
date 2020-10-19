#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int max_rec(const int a[], int from, int to) {
    if (from >= to)
        return a[from];
    else {
        int mid = (from+to) / 2;
        int max_left = max_rec(a, from, mid);
        int max_right = max_rec(a, mid + 1, to);

        return (max_left > max_right) ? max_left : max_right;
    }
}

static int max (const int a[], int length) {
    if (length<=0)
        return INT_MIN;
    return max_rec(a, 0, length - 1);
}

int main () {

    int array[] = {5, 8, 1, 3, 4, 6, 2, 0};

    int length = sizeof(array) / sizeof(int);

    int max_value = max(array, length);

    printf("Maximum: %d\nLength: %d\n", max_value, length);

    return EXIT_SUCCESS;
}