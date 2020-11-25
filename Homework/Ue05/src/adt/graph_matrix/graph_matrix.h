#ifndef GRAPH_MATRIX_H
    #define GRAPH_MATRIX_H

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

    void print_graph_matrix(graph_matrix* matrix);
    void free_graph_matrix(graph_matrix* matrix);
    void init_graph_matrix(graph_matrix* matrix);
    void add_node_to_graph_matrix(graph_matrix* matrix, char* value);
    void remove_node_from_graph_matrix(graph_matrix* matrix, char* value);
    void add_edge_matrix(graph_matrix* matrix, char* source_node, char* target_node);
    void remove_edge_matrix(graph_matrix* matrix, char* source_node, char* target_node);
    void print_sorted(graph_matrix* matrix);

#endif