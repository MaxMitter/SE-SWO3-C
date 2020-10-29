#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ARRAY_SIZE 100

void poly_print(double const p[], int const m) {
    printf("P(x) = ");
    for (int i = 0; i < m; i++) {
        if (i == 0) {
            if (p[i] != 0)
                printf("%.2f", p[i]);
        }
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
            total += p[i] * pow(x, i);
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

int poly_sub(double const p[], int const m, double const q[], int const n, double r[]) {
    int max = m > n ? m : n;

    for (int i = 0; i < max; i++) {
        r[i] = p[i] - q[i];
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
    if (m != 1) {
        double pl[ARRAY_SIZE], pr[ARRAY_SIZE], ql[ARRAY_SIZE], qr[ARRAY_SIZE], hl[ARRAY_SIZE], hr[ARRAY_SIZE], hm[ARRAY_SIZE], hm1[ARRAY_SIZE], hm2[ARRAY_SIZE];

        int half = m / 2;

        for (int i = 0; i < half; i++) {
            pl[i] = p[i];
            ql[i] = q[i];
        }

        for (int i = half; i < m; i++) {
            pr[i - half] = p[i];
            qr[i - half] = q[i];
        }

        //Calculate helping variables hl, hr, hm
        poly_mult_fast(pl, half, ql, half, hl);
        poly_mult_fast(pr, m - half, qr, m - half, hr);

        poly_add(pl, half, pr, m - half, hm1);
        poly_add(ql, half, qr, m - half, hm2);
        poly_mult_fast(hm1, m - half, hm2, m - half, hm);

        //Calculate result
        double min[ARRAY_SIZE];

        for (int i = 0; i < m * m; i++)
            min[i] = 0;

        poly_sub(hm, m-half+1, hl, half+1, min);
        poly_sub(min, m-half+1, hr, m-half+1, min);

        int mult = half;
        for (int j = m + mult; j >= mult; j--) {
            min[j] = min[j - mult];
        }
        for (int j = mult - 1; j >= 0; j--) {
            min[j] = 0;
        }

        double hrx[ARRAY_SIZE];
        int mul = m;
        for (int j = m + mul; j >= mul; j--)
            hrx[j] = hr[j - mul];
        
        for (int j = mul - 1; j >= 0; j--)
            hrx[j] = 0;

        poly_add(hl, half, min, m + mult, r);
        poly_add(r, m + mult, hrx, m + mul, r);
        return m + n - 2;
    } else {
        r[0] = p[0] * q[0];
        return 1;
    }
}

int main()
{
    double a1[] = {1, 1, 3, -4, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    double a2[] = {1, 2, -5, -3, 0, -2, 0, 0, 0, 0, 0, 0};

    double a4[] = {1, 1, 3, -4, 0, 0};
    double a5[] = {1, 2, -5, -3, 0, 0};

    double a3[ARRAY_SIZE];
    double atest[ARRAY_SIZE];
    poly_print(a1, sizeof(a1)/sizeof(double));
    poly_print(a2, 6);
    printf("Total at 3.14: %f\n", poly_evaluate(a1, 4, -3.1415926));
    poly_add(a1, 4, a2, 6, a3);
    printf("Sum of a1 + a2: ");
    poly_print(a3, 6);

    //int ret = poly_mult(a4, 4, a5, 4, a3);
    //printf("Mult of a1 * a2: %d", ret);
    //poly_print(a3, ret + 1);

    int ret = poly_mult_fast(a4, 4, a5, 4, a3);
    printf("Mult of a4 * a5: %d", ret);
    poly_print(a3, ret + 1);

    ret = poly_mult_fast(a1, 6, a2, 6, atest);
    printf("Mult of a1 * a2: %d", ret);
    poly_print(atest, ret + 1);

    return 0;
}
