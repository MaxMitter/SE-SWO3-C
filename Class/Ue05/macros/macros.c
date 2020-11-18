#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 100
#define MAX(a,b) a < b ? b : a

int main(int argc, char const *argv[])
{
    int array[MAX_LEN];
    printf("Test: %d\n", MAX(5, 7));
    return EXIT_SUCCESS;
}
