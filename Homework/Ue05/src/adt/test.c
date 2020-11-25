#include <stdio.h>

// #define USE_GRAPH_LIST
#define USE_GRAPH_MATRIX

#include "./graph.h"

int main(int argc, char const *argv[])
{
    graph g;
    init_graph(&g);
    add_node_to_graph(&g, "Test1\0");
    add_node_to_graph(&g, "Test2\0");
    add_node_to_graph(&g, "Test3\0");
    add_node_to_graph(&g, "Test4\0");
    print_graph(&g);
    
    add_edge(&g, "Test1\0", "Test2\0");
    add_edge(&g, "Test1\0", "Test3\0");
    add_edge(&g, "Test1\0", "Test4\0");
    print_graph(&g);

    remove_edge(&g, "Test1\0", "Test2\0");
    print_graph(&g);
    remove_node_from_graph(&g, "Test3\0");
    print_graph(&g);

    print_sorted(&g);

    free_graph(&g);
    print_graph(&g);
    return 0;
}
