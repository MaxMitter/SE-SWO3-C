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
        total += p[i] * pow(x, i);
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
    if (m != n)
        return -1;
    if (m != 1) {
        if (m % 2 != 0)
            return -1;

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
        double hrx[ARRAY_SIZE];

        for (int i = 0; i < m * m; i++) {
            min[i] = 0;
            hrx[i] = 0;
        }

        poly_sub(hm, m-half+1, hl, half+1, min);
        poly_sub(min, m-half+1, hr, m-half+1, min);

        int mult = half;
        for (int j = m + mult; j >= mult; j--) {
            min[j] = min[j - mult];
        }
        for (int j = mult - 1; j >= 0; j--) {
            min[j] = 0;
        }

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
    // Test poly_print //
    double a1[] = {1, 1, 3, -4, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    double a2[] = {1, 2, -5, -3, 6, 3, 15, 9115, 5, -3654, 20, 11};

    double a3[] = {1, 1, 3, 0, 0, 0};
    double a4[] = {0, 0, 0, 0, 0, 0};

    printf("Test a1: ");
    poly_print(a1, 4);
    printf("Test a2: ");
    poly_print(a2, 12);
    printf("Test a3: ");
    poly_print(a3, 6);
    printf("Test a4: ");
    poly_print(a4, 6);
    printf("----------------------------------------------------------------\n");

    // Test poly_evaluate //
    printf("Testing with the function "); poly_print(a1, 4);
    printf("Total at -3.14: %.2f\n", poly_evaluate(a1, 4, -3.1415926));
    printf("Total at 3.14: %.2f\n", poly_evaluate(a1, 4, 3.1415926));
    printf("Total at 0: %.2f\n", poly_evaluate(a1, 4, 0));
    printf("Total at 10 %.2f\n", poly_evaluate(a1, 4, 10));
    printf("Total at -10: %.2f\n", poly_evaluate(a1, 4, -10));
    printf("Total at 250: %.2f\n", poly_evaluate(a1, 4, 250));
    printf("----------------------------------------------------------------\n");

    // Test poly_add //
    double polyadd1[] = {1, 1, 3, -4, 0};
    double polyadd2[] = {1, 2, -5, -3, 0, -2};
    double polyadd3[] = {0, 0, 0, 0, 0, 0, 0, 0};
    double polyadd4[] = {102, 15, 33, 752, 0, 0};

    double polyresult[ARRAY_SIZE];

    poly_add(polyadd1, 4, polyadd2, 6, polyresult);
    printf("Sum of polyadd1 + polyadd2: ");
    poly_print(polyresult, 6);

    poly_add(polyadd2, 6, polyadd3, 6, polyresult);
    printf("Sum of polyadd2 + polyadd3: ");
    poly_print(polyresult, 6);

    poly_add(polyadd1, 4, polyadd4, 4, polyresult);
    printf("Sum of polyadd1 + polyadd4: ");
    poly_print(polyresult, 6);

    poly_add(polyadd4, 4, polyadd3, 6, polyresult);
    printf("Sum of polyadd4 + polyadd3: ");
    poly_print(polyresult, 6);

    printf("----------------------------------------------------------------\n");

    // Test poly_mult //
    double polymult1[] = {1, 1, 3, -4, 0, 0};
    double polymult2[] = {1, 2, -5, -3, 0, -2};
    double polymult3[] = {1, 0, 0, 0, 0, 0, 0};
    double polymult4[] = {102, 15, 33, 752, 314};

    int ret = poly_mult(polymult1, 4, polymult2, 6, polyresult);
    printf("Mult of polymult1 * polymult2 (Grade: %d): ", ret);
    poly_print(polyresult, ret + 1);

    ret = poly_mult(polymult1, 4, polymult3, 6, polyresult);
    printf("Mult of polymult1 * polymult3 (Grade: %d): ", ret);
    poly_print(polyresult, ret + 1);

    ret = poly_mult(polymult2, 6, polymult4, 5, polyresult);
    printf("Mult of polymult2 * polymult4 (Grade: %d): ", ret);
    poly_print(polyresult, ret + 1);

    ret = poly_mult(polymult3, 6, polymult4, 5, polyresult);
    printf("Mult of polymult3 * polymult4 (Grade: %d): ", ret);
    poly_print(polyresult, ret + 1);

    printf("----------------------------------------------------------------\n");

    // Test poly_mult_fast //
    double polymultfast1[] = {1, 1, 3, -4, 0, 0};
    double polymultfast2[] = {1, 2, -5, -3, 0, 0};
    double polymultfast3[] = {1, 0, 0, 0, 0, 0, 0};
    double polymultfast4[] = {102, 15, 33, 752};

    ret = poly_mult_fast(polymult1, 4, polymult2, 4, polyresult);
    if (ret == -1) {
        printf("Invalid grade of polynome\n");
        return EXIT_FAILURE;
    }
    printf("Fast Mult of polymultfast1 * polymultfast2 (Grade: %d): ", ret);
    poly_print(polyresult, ret + 1);

    ret = poly_mult_fast(polymult1, 4, polymult3, 4, polyresult);
    if (ret == -1) {
        printf("Invalid grade of polynome\n");
        return EXIT_FAILURE;
    }
    printf("Fast Mult of polymultfast1 * polymultfast3 (Grade: %d): ", ret);
    poly_print(polyresult, ret + 1);

    ret = poly_mult_fast(polymult2, 4, polymult4, 4, polyresult);
    if (ret == -1) {
        printf("Invalid grade of polynome\n");
        return EXIT_FAILURE;
    }
    printf("Fast Mult of polymultfast2 * polymultfast4 (Grade: %d): ", ret);
    poly_print(polyresult, ret + 1);

    ret = poly_mult_fast(polymult3, 1, polymult4, 4, polyresult);
    if (ret == -1) {
        printf("Invalid grade of polynome\n");
        return EXIT_FAILURE;
    }
    printf("Fast Mult of polymultfast3 * polymultfast4 (Grade: %d): ", ret);
    poly_print(polyresult, ret + 1);

    printf("----------------------------------------------------------------\n");

    return 0;
}
