#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

    #ifndef bool
        #define bool int
        #define true 1
        #define false 0
    #endif

    #ifndef INIT_SIZE
        #define INIT_SIZE 4
    #endif

    typedef struct node_array {
        char* value;
    } node_array;

    typedef struct graph_matrix {
        node_array* nodes;
        int matrix_size;
        int count_elements;
        bool* edges;
    } graph_matrix;

void print_graph_matrix(graph_matrix* matrix) {
    if (matrix->matrix_size == 0) {
        printf("Matrix is not initialized!\n");
        return;
    }
    printf("      |");
    int size = matrix->matrix_size;
    for (int i = 0; i < size; i++) {
        if (matrix->nodes[i].value != NULL)
            printf(" %5s", matrix->nodes[i].value);
    }

    for (int i = 0; i < size * size; i++) {
        if (matrix->nodes[(int)floor(i / matrix->matrix_size)].value != NULL) {
            if (i % matrix->matrix_size == 0) {
                printf("\n");
                printf("%5s |", matrix->nodes[(int)floor(i / matrix->matrix_size)].value);
            }
            printf("%5d", matrix->edges[i]);
        }
    }
    printf("\n");
}

int get_node_id(graph_matrix* matrix, char* value) {
    for (int i = 0; i < matrix->count_elements; i++) {
        if (!strcmp(matrix->nodes[i].value, value))
            return i;
    }
    return -1;
}

void init_edge_matrix(graph_matrix* matrix, int size) {
    for (int i = 0; i < size; i++) {
        matrix->edges[i] = false;
    }
}

void init_graph_matrix_size(graph_matrix* matrix, int size) {
    matrix->matrix_size = size;
    matrix->count_elements = 0;
    matrix->nodes = malloc(sizeof(node_array) * size);
    if (matrix->nodes == NULL) {
        printf("Error while allocating memory for nodes, aborting.\n");
        exit;
    }
    matrix->edges = malloc(sizeof(bool) * size*size);
    if (matrix->edges == NULL) {
        printf("Error while allocating memory for edges, aborting.\n");
        exit;
    }
    init_edge_matrix(matrix, size);
}

void init_graph_matrix(graph_matrix* matrix) {
    init_graph_matrix_size(matrix, INIT_SIZE);
}

void free_graph_matrix(graph_matrix* matrix) {
    for (int i = 0; i < matrix->matrix_size; i++) {
        free(matrix->nodes[i].value);
        matrix->nodes[i].value = NULL;
    }
    free(matrix->nodes);
    matrix->nodes = NULL;
    free(matrix->edges);
    matrix->edges = NULL;

    matrix->count_elements = 0;
    matrix->matrix_size = 0;
}

void insert_node(graph_matrix* matrix, char* value) {
    matrix->nodes[matrix->count_elements].value = malloc((strlen(value) + 1) * sizeof(char));
    strcpy(matrix->nodes[matrix->count_elements].value, value);
    matrix->count_elements++;
}

void enlarge_matrix(graph_matrix* matrix) {
    printf("Enlarging matrix...\n");
    static graph_matrix new_matrix;
    init_graph_matrix_size(&new_matrix, matrix->matrix_size * 2);
    for (int i = 0; i < matrix->count_elements; i++) {
        insert_node(&new_matrix, matrix->nodes[i].value);
    }

    for (int i = 0; i < matrix->matrix_size * matrix->matrix_size; i++) {
        int row = (int)floor(i/matrix->matrix_size);
        int col = i % matrix->matrix_size;
        new_matrix.edges[row * new_matrix.matrix_size + col] = matrix->edges[i];
    }

    free_graph_matrix(matrix);
    matrix->nodes = new_matrix.nodes;
    matrix->edges = new_matrix.edges;
    matrix->count_elements = new_matrix.count_elements;
    matrix->matrix_size = new_matrix.matrix_size;
    printf("Done!\n");
}

void add_node_to_graph_matrix(graph_matrix* matrix, char* value) {
    if (matrix->count_elements == matrix->matrix_size) {
        enlarge_matrix(matrix);
    }
    insert_node(matrix, value);
}

void add_edge_matrix(graph_matrix* matrix, char* source_node, char* target_node) {
    int source_node_id = get_node_id(matrix, source_node);
    int target_node_id = get_node_id(matrix, target_node);
    if (source_node_id == -1 || target_node_id == -1) {
        printf("Error while adding edge: Node(s) not found!\n");
        exit;
    }
    matrix->edges[target_node_id * matrix->matrix_size + source_node_id] = true;
}

void remove_edge_matrix(graph_matrix* matrix, char* source_node, char* target_node) {
    int source_node_id = get_node_id(matrix, source_node);
    int target_node_id = get_node_id(matrix, target_node);
    if (source_node_id == -1 || target_node_id == -1) {
        printf("Error while removing edge: Node(s) not found!\n");
        exit;
    }
    matrix->edges[target_node_id * matrix->matrix_size + source_node_id] = 0;
}

void remove_node_from_graph_matrix(graph_matrix* matrix, char* value) {
    int remove_node_id = get_node_id(matrix, value);
    if (remove_node_id == -1) {
        printf("Error while removing Node '%s', aborting!\n", value);
        exit;
    }
    // deleting column
    for (int i = 0; i < matrix->count_elements; i++) {
        for (int j = remove_node_id + i * matrix->count_elements; j < matrix->count_elements + i * matrix->matrix_size; j++) {
            matrix->edges[j] = matrix->edges[j + 1];
        }
    }

    // deleting row
    for (int i = 0; i < matrix->count_elements; i++) {
        for (int j = remove_node_id * matrix->matrix_size + i; j < (matrix->count_elements - 1) * matrix->matrix_size; j += matrix->matrix_size) {
            matrix->edges[i] = matrix->edges[j + matrix->matrix_size];
        }
    }

    // removing value

    free(matrix->nodes[remove_node_id].value);
    for (int i = remove_node_id + 1; i < matrix->count_elements; i++) {
        matrix->nodes[i - 1] = matrix->nodes[i];
    }
    matrix->nodes[matrix->count_elements - 1].value = NULL;

    matrix->count_elements--;
}

int main(int argc, char const *argv[])
{
    graph_matrix g;
    init_graph_matrix(&g);
    add_node_to_graph_matrix(&g, "Test1\0");
    add_node_to_graph_matrix(&g, "Test2\0");
    add_node_to_graph_matrix(&g, "Test3\0");
    add_node_to_graph_matrix(&g, "Test4\0");
    print_graph_matrix(&g);

    add_node_to_graph_matrix(&g, "Test5\0");
    add_node_to_graph_matrix(&g, "Test6\0");
    add_node_to_graph_matrix(&g, "Test7\0");

    add_edge_matrix(&g, "Test1\0", "Test2\0");
    add_edge_matrix(&g, "Test1\0", "Test3\0");
    add_edge_matrix(&g, "Test1\0", "Test6\0");
    add_edge_matrix(&g, "Test1\0", "Test7\0");
    add_edge_matrix(&g, "Test3\0", "Test6\0");
    print_graph_matrix(&g);

    remove_node_from_graph_matrix(&g, "Test1\0");
    print_graph_matrix(&g);
    free_graph_matrix(&g);
    print_graph_matrix(&g);
    return 0;
}
