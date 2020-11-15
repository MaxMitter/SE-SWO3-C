#include <string.h>
#include <stdio.h>
#include <limits.h>

#include "matrix.h"
#include "helper.h"

void calculate_levenshtein(matrix_element matrix[MAX_ROWS][MAX_COLS], int const rows, int const cols, char text_left[], char text_top[]) {
    for (int r = 1; r < rows; r++) {
        for (int c = 1; c < cols; c++) {
            if (text_top[c - 1] == text_left[r - 1]) {
                matrix[r][c].value = min_of_three(matrix[r - 1][c].value + 1, matrix[r][c - 1].value + 1, matrix[r - 1][c - 1].value);
            } else {
                matrix[r][c].value = min_of_three(matrix[r - 1][c].value + 1, matrix[r][c - 1].value + 1, matrix[r - 1][c - 1].value + 1);
            }

            matrix[r][c].from_left = (matrix[r][c].value == matrix[r][c - 1].value + 1);
            matrix[r][c].from_top = (matrix[r][c].value == matrix[r - 1][c].value + 1);
            matrix[r][c].from_topleft = ((matrix[r][c].value == matrix[r - 1][c - 1].value) && (text_left[r - 1] == text_top[c - 1])) || (matrix[r][c].value == matrix[r - 1][c - 1].value + 1);
        }
    }
}

void print_sequence(char text_left[], char text_top[], char sequence[]) {
    printf("w |");
    int i = 0;
    int seq_counter = 0;
    int len = strlen(text_top);
    int seq_len = strlen(sequence);

    while (seq_counter <= seq_len) {
        if (sequence[seq_counter] == 'i') {
            printf("   ");
        } else {
            if (i < len) {
                printf(" %c ", text_top[i]);
                i++;
            }
        }
        seq_counter++;
    }
    NEW_LINE;

    printf("v |");
    i = 0;
    seq_counter = 0;
    len = strlen(text_left);
    while (seq_counter <= seq_len) {
        if (sequence[seq_counter] == 'd') {
            printf("   ");
        } else {
            if (i < len) {
                printf(" %c ", text_left[i]);
                i++;
            }
        }
        seq_counter++;
    }
    NEW_LINE;

    printf("  |");
    for (i = 0; i < strlen(sequence); i++) {
        printf(" %c ", sequence[i]);
    }
    NEW_LINE;
}

int count = 1;

void calculate_and_print_editsequence(matrix_element m[MAX_ROWS][MAX_COLS], int const rows, int const cols, char text_left[], char text_top[],
                            char const sequence[MAX_SIZE]) {
    if (rows <= 1 && cols <= 1) {
        printf("Sequence #%d\n", count);
        print_sequence(text_left, text_top, sequence);
        count++;
    } else {
        if (m[rows - 1][cols - 1].from_topleft) {
            if (text_top[cols - 2] == text_left[rows - 2]) {
                char shelper[MAX_SIZE] = " ";
                strcat(shelper, sequence);
                calculate_and_print_editsequence(m, rows - 1, cols - 1, text_left, text_top, shelper);
            } else {
                char shelper[MAX_SIZE] = "c";
                strcat(shelper, sequence);
                calculate_and_print_editsequence(m, rows - 1, cols - 1, text_left, text_top, shelper);
            }
        }

        if (m[rows - 1][cols - 1].from_top) {
            char shelper[MAX_SIZE] = "i";
            strcat(shelper, sequence);
            calculate_and_print_editsequence(m, rows - 1, cols, text_left, text_top, shelper);
        }

        if (m[rows - 1][cols - 1].from_left) {
            char shelper[MAX_SIZE] = "d";
            strcat(shelper, sequence);
            calculate_and_print_editsequence(m, rows, cols - 1, text_left, text_top, shelper);
        }
    }
}

void calculate_lcq(matrix_element m[MAX_ROWS][MAX_COLS], int const rows, int const cols, char text_left[], char text_top[]) {
    for (int r = 1; r < rows; r++) {
        for (int c = 1; c < cols; c++) {
            if (text_top[c - 1] == text_left[r - 1]) {
                m[r][c].value = max_of_three(m[r - 1][c].value, m[r][c - 1].value, m[r - 1][c - 1].value + 1);
            } else {
                m[r][c].value = max_of_three(m[r - 1][c].value, m[r][c - 1].value, m[r - 1][c - 1].value);
            }

            m[r][c].from_left = (m[r][c].value == m[r][c - 1].value);
            m[r][c].from_top = (m[r][c].value == m[r - 1][c].value);
            m[r][c].from_topleft = ((m[r][c].value == m[r - 1][c - 1].value + 1) && (text_left[r - 1] == text_top[c - 1])) || (m[r][c].value == m[r - 1][c - 1].value);
        }
    }
}

int get_min_of_row(matrix_element m[MAX_COLS], int const cols) {
    int min = INT_MAX;
    for (int i = 0; i < cols; i++) {
        min = min < m[i].value ? min : m[i].value;
    }
    return min;
}

int print_pattern(char text[], char pattern[], int const position, int const sequence) {
    printf("Position #%d\n", sequence);
    
    printf("%s\n", text);
    int pattern_len = strlen(pattern);
    for (int i = 0; i < (position - pattern_len); i++)
        printf(" ");

    printf("%s\n", pattern);

    return sequence + 1;
}

void find_and_print_bestmatch(matrix_element m[MAX_ROWS][MAX_COLS], int const rows, int const cols, char text_left[], char text_top[]) {
    int min = get_min_of_row(m[rows], cols);

    int sequence = 1;
    for (int i = 0; i < cols; i++) {
        if (m[rows][i].value == min) {
            sequence = print_pattern(text_top, text_left, i, sequence);
        }
    }

}

int main()
{
    // Levenshtein-distance //
    matrix_element matrix[MAX_ROWS][MAX_COLS] = { {0} };
    init_matrix(matrix, MAX_ROWS, MAX_COLS, 0);
    // TGCATA
    // ATCTGAT
    // cc d i i
    char test1[] = "ATCTGAT\0";
    int str1len = strlen(test1);
    char test2[] = "TGCATA\0";
    int str2len= strlen(test2);

    calculate_levenshtein(matrix, str1len + 1, str2len + 1, test1, test2);
    print_matrix(matrix, str1len + 1, str2len + 1, test1, test2);
    printf("Levenshtein-Distance: %d\n", matrix[str1len][str2len].value);

    char sequence[MAX_SIZE] = "\0";
    calculate_and_print_editsequence(matrix, str1len + 1, str2len + 1, test1, test2, sequence);

    // Longest common subsequence //
 
    printf("-----------------LCQ-----------------\n");
    count = 1;
    matrix_element m[MAX_ROWS][MAX_COLS] = { {0} };
    init_matrix(m, MAX_ROWS, MAX_COLS, 1);
    calculate_lcq(m, str1len + 1, str2len + 1, test1, test2);
    print_matrix(m, str1len + 1, str2len + 1, test1, test2);
    printf("Longest common subsequence: %d\n", m[str1len][str2len].value);

    calculate_and_print_editsequence(m, str1len + 1, str2len + 1, test1, test2, sequence);

    // Approx String Matching //
    printf("-----------------ASM-----------------\n");
    matrix_element search[MAX_ROWS][MAX_COLS] = { {0} };
    init_matrix(search, MAX_ROWS, MAX_COLS, 2);

    char text[] = "DONAUDAMPFSCHIFFFARHTSKAPITAENSKAJUETE\0";
    char pattern[] = "FLUSSFAHRT\0";
    int text_len = strlen(text);
    int pattern_len = strlen(pattern);

    calculate_levenshtein(search, pattern_len + 1, text_len + 1, pattern, text);
    print_matrix(search, pattern_len + 1, text_len + 1, pattern, text);
    find_and_print_bestmatch(search, pattern_len, text_len, pattern, text);

    return 0;
}