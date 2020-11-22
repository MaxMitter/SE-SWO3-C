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
    void add_node_to_graph_list(graph_list *list, char *value);
    void print_graph_list(graph_list* list);
    void free_graph_list(graph_list* list);
    void remove_node_from_graph_list(graph_list* list, char* value);
    bool node_in_graph_list(graph_list* list, char* value);
    void add_vertex_list(graph_list* list, char* source_node, char* target_node);
    bool vertex_in_node_list(list* vertex_list, char* target);
    void remove_vertex_list(graph_list* graph, char* source_node, char* target_node);
#endif