#include <stdio.h>

#define USE_GRAPH_LIST
//#define USE_GRAPH_MATRIX

#include "./graph.h"

int main(int argc, char const *argv[])
{
    graph g;
    init_graph(&g);
    add_graph_node(&g, "Test1\0");
    add_graph_node(&g, "Test2\0");
    add_graph_node(&g, "Test3\0");
    add_graph_node(&g, "Test4\0");
    print_graph(&g);
    remove_node_from_graph(&g, "Test4\0");
    print_graph(&g);
    free_graph(&g);
    print_graph(&g);
    return 0;
}
