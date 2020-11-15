#define bool int
#define true 1
#define false 0

#define MAX_ROWS 100
#define MAX_COLS 100

#define MAX_SIZE (MAX_ROWS * MAX_COLS)
#define NEW_LINE printf("\n")
#define PRINT_LINE printf("--------------------------------------\n")

typedef struct matrix_element {
    int value;
    bool from_left;
    bool from_top;
    bool from_topleft;
} matrix_element;

void print_matrix (matrix_element matrix[MAX_ROWS][MAX_COLS], int const rows, int const cols, char text_left[], char text_top[]);
void init_matrix (matrix_element matrix[MAX_ROWS][MAX_COLS], int const rows, int const cols, int init_type);