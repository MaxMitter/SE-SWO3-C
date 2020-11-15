#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

void print_matrix (matrix_element matrix[MAX_ROWS][MAX_COLS], int const rows, int const cols, char text_left[], char text_top[]) {
    printf("      ");

    for (int i = 0; i < cols; i++)
        printf(" %c ", text_top[i]);
    
    NEW_LINE;

    for (int r = 0; r < rows; r++) {
        if (r == 0)
            printf("   ");
        else
            printf(" %c ", text_left[r - 1]);
        for (int c = 0; c < cols; c++) {
            printf("%2d ", matrix[r][c].value);
        }
        NEW_LINE;
    }
    PRINT_LINE;
}


// Init Type describes, how the matrix should be initialized
// 0 = Init for Levenshtein
// 1 = Init for Longest Subsequence
// 2 = Init for approximate String Matching
void init_matrix (matrix_element matrix[MAX_ROWS][MAX_COLS], int const rows, int const cols, int init_type) {
    switch (init_type)
    {
    case 0:
        for (int i = 0; i < rows; i++) {
            matrix[i][0].value = i;
            matrix[i][0].from_top = true;
        }
        for (int i = 0; i < cols; i++) {
            matrix[0][i].value = i;
            matrix[0][i].from_left = true;
        }
        break;
    case 1:
        for (int i = 0; i < rows; i++) {
            matrix[i][0].value = 0;
            matrix[i][0].from_top = true;
        }
        for (int i = 0; i < cols; i++) {
            matrix[0][i].value = 0;
            matrix[0][i].from_left = true;
        }
        break;
    case 2:
        for (int i = 0; i < rows; i++) {
            matrix[i][0].value = i;
            matrix[i][0].from_top = true;
        }
        for (int i = 0; i < cols; i++) {
            matrix[0][i].value = 0;
            matrix[0][i].from_left = true;
        }
        break;
    }
}