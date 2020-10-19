#include <stdio.h>

//variante 1
//const int MAX = 5;

#define MAX 6
#define MAX_LENGTH 5

static void show_datatype_sizes() {
    printf("sizeof(int)=%ld\n", sizeof(int));
    printf("sizeof(char)=%ld\n", sizeof(char));
    printf("sizeof(short)=%ld\n", sizeof(short));
    printf("sizeof(long)=%ld\n", sizeof(long));
    printf("sizeof(long long)=%ld\n", sizeof(long long));
    printf("sizeof(float)=%ld\n", sizeof(float));
    printf("sizeof(double)=%ld\n", sizeof(double));
    printf("sizeof(long double)=%ld\n", sizeof(long double));
    printf("sizeof(int *)=%ld\n", sizeof(int *));
}

static void show_casts() {
    int input = 1;
    double result = input/3.0;

    printf("result = %f\n", result);
}

static void play_with_arrays () {
    int array[MAX_LENGTH];

    for (int i = 0; i<MAX_LENGTH;i++) {
        printf("%p, %d\n", (void *)(array+i), array[i]);
        //array[i] == *(array+i)
    }
}

int main() {
    int i;

    for (i = 0; i < MAX; i++)
        printf("%i ", i);
    printf("\n");

    //show_datatype_sizes();
    //show_casts();
    play_with_arrays();

    return EXIT_SUCCESS;
}