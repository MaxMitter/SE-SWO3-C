#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    int value, count;
    for (int i = 1; i < argc; i++) {
        value = atoi(argv[i]);
        if (value < 0) {
            printf("Number has to be > 0\n");
            return 0;
        } else {
            printf("%10d: {", value);
            for (int prim = 2; prim < value; prim++) {
                if (isPrime(prim)) {
                    count = 0;
                    while (value % prim == 0) {
                        value /= prim;
                        count++;
                    }
                    if (count != 0)
                        printf("{%d,%d},", prim, count);
                }
            }
            if (isPrime(value))
                printf("{%d,1}", value);
            printf("}\n");
        }
    }
    return 0;
}

int isPrime(int x) {
    for (int i = 2; i <= x / 2; ++i) {
        if (x % i == 0)
            return 0;
    }

    return 1;
}