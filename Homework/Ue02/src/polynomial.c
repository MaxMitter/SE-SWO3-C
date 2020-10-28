#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ARRAY_SIZE 100

void poly_print(double const p[], int const m) {
    printf("P(x) = ");
    for (int i = 0; i < m; i++) {
        if (i == 0)
            printf("%.2f", p[i]);
        else if (i == 1) {
            if (p[i] > 0)
                printf(" + %.2f*x", p[i]);
            else if (p[i] < 0)
                printf(" - %.2f*x", p[i] * - 1);
        } else {
            if (p[i] > 0)
                printf(" + %.2f*x^%d", p[i], i);
            else if (p[i] < 0)
                printf(" - %.2f*x^%d", p[i] * - 1, i);
        }
    }
    printf("\n");
}

double poly_evaluate(double const p[], int const m, double const x) {
    double total = 0;
    for (int i = 0; i < m; i++) {
        if (i == 0)
            total += p[i];
        else {
            int exp = 1;
            total += p[i] * pow(x, i);
            //for (int j = 0; j <= i; j++)
            //    exp = exp * p[i];
            
            total += exp;
        }
    }
    return total;
}

int poly_add(double const p[], int const m, double const q[], int const n, double r[]) {
    int max = m > n ? m : n;

    for (int i = 0; i < max; i++) {
        r[i] = p[i] + q[i];
    }
    return 0;
}

int poly_mult(double const p[], int const m, double const q[], int const n, double r[]) {
    int i;

    for (i = 0; i < m + n; i++)
        r[i] = 0;

    for (i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            r[i+j] += p[i] * q[j];
    }
    return m + n - 2;
}

int poly_mult_fast(double const p[], int const m, double const q[], int const n, double r[]) {
    for (int i = 0; i < m + n; i++)
        r[i] = 0;

    if (m < 2 && n < 2) {
        
    }
}

int main()
{
    double a1[] = {4, 3, -2, 1, 0, 0};
    double a2[] = {6, 7, -8, 9, 5, 3};

    double a4[] = {1, 1, 3, -4, 0, 0};
    double a5[] = {1, 2, -5, -3, 0, -2};

    double a3[ARRAY_SIZE];
    poly_print(a1, sizeof(a1)/sizeof(double));
    poly_print(a2, 6);
    printf("Total at 3.14: %f\n", poly_evaluate(a1, 4, -3.1415926));
    poly_add(a1, 4, a2, 6, a3);
    printf("Sum of a1 + a2: ");
    poly_print(a3, 6);

    int ret = poly_mult(a4, 4, a5, 6, a3);
    printf("Mult of a1 * a2: %d", ret);
    poly_print(a3, ret + 1);

    printf("\n\n\nTESTTEST: %f\n", pow(3, 3));
    return 0;
}
