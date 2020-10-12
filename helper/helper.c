#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    FILE* fp;
    sprintf("\"%s\"", argv[2]);
    fp = fopen(argv[2], "w");

    if(!fp) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }
}