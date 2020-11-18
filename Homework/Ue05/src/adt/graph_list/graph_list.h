#ifndef GRAPH_LIST_H
    #define GRAPH_LIST_H
    
    #ifndef bool
        #define bool int
        #define true 1
        #define false 0
    #endif

    typedef struct list_element* list;
    typedef struct list_element {
        char* value;
        list next;
    } list_element;

    typedef struct graph_list_element* graph_list;
    typedef struct graph_list_element {
        char* value;
        list vertex_list;
        graph_list next;
    } graph_list_element;

    void init_graph_list(graph_list* list);
    void add_graph_node_list(graph_list* list, char *value);
    void print_graph_list(graph_list* list);
    void free_graph_list(graph_list* list);
    void remove_node_from_graph_list(graph_list* list, char* value);

#endif