#ifndef GRAPH_H
#define GRAPH_H

#include "./graph_list/graph_list.h"
#include "./graph_matrix/graph_matrix.h"

#if defined USE_GRAPH_LIST
    typedef graph_list graph;

    #define print_graph print_graph_list
    #define init_graph init_graph_list
    #define add_node_to_graph add_node_to_graph_list
    #define free_graph free_graph_list
    #define remove_node_from_graph remove_node_from_graph_list
    #define add_vertex add_vertex_list
    #define node_in_graph node_in_graph_list
    #define vertex_in_node vertex_in_node_list
    #define remove_vertex remove_vertex_list

#elif defined USE_GRAPH_MATRIX
    typedef graph_matrix graph_t;

    #define print_graph print_graph_matrix
    #define init_graph init_graph_matrix
#else
    #error "Define (just) one of 'USE_GRAPH_LIST' or 'USE_GRAPH_MATRIX'."
#endif

#endif