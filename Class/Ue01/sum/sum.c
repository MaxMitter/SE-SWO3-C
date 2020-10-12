#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    int sum = 0, value;
    if (argc <= 1) {
        printf("sum = 0\n");
    } else {
        for(int i = 1; i < argc; i++) {
            value = atoi(argv[i]);
            sum += value;
            if (i == argc - 1) {
                printf("%d", value);
            } else {
                printf("%d + ", value);
            }
        }
        printf(" = %d\n", sum);
    }
    return 0;
}