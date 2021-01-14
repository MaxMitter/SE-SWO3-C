#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    for (int i = 0; i < 1250; i++) {
        printf("%d", rand() % 2);
    }
    return 0;
}
