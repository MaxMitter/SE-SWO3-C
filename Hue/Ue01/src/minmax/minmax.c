#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    int min = 0, max = 0;
    int value;

    if (argc <= 1) {
        printf("Please add more numbers\n");
    } else {
        for (int i = 1; i < argc; i++) {
            value = atoi(argv[i]);

            if (value >= 0) {
                if (value > max)
                    max = value;
            } else {
                if (value < min)
                    min = value;
            }
        }
        printf("Minimum: %d | Maximum: %d\n", min, max);
    }

    return 0;
}