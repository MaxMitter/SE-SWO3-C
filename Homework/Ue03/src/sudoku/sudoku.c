#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define bool  int
#define false 0
#define true  1
#define SUDOKU_SIZE 81

void print_sudoku(int problem[]);

bool is_solved(int problem[]) {
    for (int i = 0; i < SUDOKU_SIZE; i++) {
        if (problem[i] == 0)
            return false;
    }
    return true;
}

bool solve_sudoku(int problem[], int start_point) {
    for (int i = start_point; i < SUDOKU_SIZE; i++) {
        if (problem[i] == 0) {
            for (int j = 1; j <= 9; j++) {
                if (correct_number(problem, i, j)) {
                    problem[i] = j;
                    if (solve_sudoku(problem, i + 1))
                        return true;
                    else
                        continue;
                } else
                    problem[i] = 0;
            }
            problem[i] = 0;
            return false;
        }
    }
    return true;
}

void sudoku(int grid[]) {
    if (is_solved(grid)){
        printf("Sudoku is solved!");
        print_sudoku(grid);
    } else {
        solve_sudoku(grid, 0);
    }
}

bool correct_number(int problem[], int pos, int number) {
    int size = sqrt(SUDOKU_SIZE);

    int row = floor(pos / size);
    int col = pos - row * size;

    //check for number in this row
    for (int i = row * size; i < (row + 1) * size; i++) {
        if (problem[i] == number)
            return false;
    }

    //check for number in this col
    for (int i = col; i <= col + (size - 1) * size; i += size) {
        if (problem[i] == number)
            return false;
    }

    //check for number in subgrid
    int start_col, end_col = 0;
    int start_row, end_row = 0;
    if (col % 3 == 0) {
        start_col = col;
        end_col = col + 2;
    } else if (col % 3 == 1) {
        start_col = col - 1;
        end_col = col + 1;
    } else {
        start_col = col - 2;
        end_col = col;
    }

    if (row % 3 == 0) {
        start_row = row;
        end_row = row + 2;
    } else if (row % 3 == 1) {
        start_row = row - 1;
        end_row = row + 1;
    } else {
        start_row = row - 2;
        end_row = row;
    }

    for (int i = start_row; i <= end_row; i++) {
        for (int j = start_col; j <= end_col; j++) {
            int cur_pos = i * 9 + j;
            if (problem[cur_pos] == number)
                return false;
        }
    }

    return true;
}

void print_sudoku(int problem[]) {
    int size = sqrt(SUDOKU_SIZE);
    int counter = 0;
    printf("-------------------------------------\n");
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if (problem[counter] == 0)
                printf(". ");
            else              
                printf("%d ", problem[counter]);
            if (counter % 3 == 2)
                printf("  ");
            counter++;
        }
        if (i % 3 == 2)
            printf("\n");

        printf("\n");
    }
}

int main(int argc, char const *argv[])
{
    int problem[SUDOKU_SIZE] = { 0, 0, 4, 0, 0, 0, 0, 6, 7, 3, 0, 0, 4, 7, 0, 0, 0, 5, 1, 5, 0, 8, 2, 0, 0, 0, 3, 0, 0, 6, 0, 0, 0, 0, 3, 1, 8, 0, 2, 1, 0, 5, 6, 0, 4, \
                                4, 1, 0, 0, 0, 0, 9, 0, 0, 7, 0, 0, 0, 8, 0, 0, 4, 6, 6, 0, 0, 0, 1, 2, 0, 0, 0, 9, 3, 0, 0, 0, 0, 7, 1, 0};
    int test2[SUDOKU_SIZE] = {0, 0, 0, 2, 6, 0, 7, 0, 1, 6, 8, 0, 0, 7, 0, 0, 9, 0, 1, 9, 0, 0, 0, 4, 5, 0, 0, 8, 2, 0, 1, 0, 0, 0, 4, 0, 0, 0, 4, 6, 0, 2, 9, 0, 0, 0, 5, \
                                0, 0, 0, 3, 0, 2, 8, 0, 0, 9, 3, 0, 0, 0, 7, 4, 0, 4, 0, 0, 5, 0, 0, 3, 6, 7, 0, 3, 0, 1, 8, 0, 0, 0};
    int test3[SUDOKU_SIZE] = {0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 3, 0, 7, 4, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 2, 0, 8, 0, 0, 4, 0, 0, 1, 0, \
                                6, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 7, 8, 0, 5, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0};
    clock_t time_before, time_after;
    
    print_sudoku(test3);

    time_before = clock();
    sudoku(test3);
    time_after = clock();
    print_sudoku(test3);

    double duration = 1000.0*(time_after - time_before)/CLOCKS_PER_SEC;

    printf("Time taken: %.2f ms\n", duration);
    return 0;
}