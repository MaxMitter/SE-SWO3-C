#include "./graph_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void print_graph_list(graph_list *list){
    printf("Printing Graph List:\n");
    graph_list list_iterator = *list;
    while (list_iterator != NULL) {
        printf("'%s' | V: ", list_iterator->value);

        //TODO print vertices
        printf("\n");
        list_iterator = list_iterator->next;
    }
}

void init_graph_list(graph_list *list) {
    *list = NULL;
}

graph_list_element* new_node_list(char *value) {
    graph_list_element *node = malloc(sizeof(graph_list_element));
    if (node == NULL) {
        printf("Memory allocation while adding Node '%s', aborting.", value);
        exit;
    }
    node->value = malloc(strlen(value) * sizeof(char));
    node->value = value;
    node->vertex_list = NULL;
    node->next = NULL;
    return node;
}

void append_list (graph_list* list, graph_list_element* node) {
    graph_list list_iterator = *list;
    if (list_iterator == NULL)
        *list = node;
    else {
        while (list_iterator->next != NULL) {
            list_iterator = list_iterator->next;
        }
        list_iterator->next = node;
    }
}

bool node_in_graph(graph_list *list, char *value) {
    graph_list node_iterator = *list;
    while (node_iterator != NULL) {
        if (!strcmp(node_iterator->value, value)) {
            return true;
        }
        node_iterator = node_iterator->next;
    }
    return false;
}

void add_graph_node_list(graph_list *list, char *value) {
    if (!node_in_graph(list, value))
        append_list(list, new_node_list(value));
    else
        printf("Node '%s' already in graph!\n", value);
}

void remove_node_from_graph_list(graph_list* list, char* value) {
    if (node_in_graph(list, value)) {
        graph_list list_iterator = *list;
        graph_list_element *prev = NULL;
        while (list_iterator != NULL) {
            if(!strcmp(list_iterator->value, value))
                break;
            prev = list_iterator;
            list_iterator = list_iterator->next;
        }

        if (list_iterator != NULL) {
            if (prev != NULL)
                prev->next = list_iterator->next;
            else
                *list = list_iterator->next;
            
            free(list_iterator);
        }
    } else
        printf("Node '%s' could not be removed: Node not found!", value);
}

void free_graph_list(graph_list *list) {
    graph_list n = *list;
    if (n->next != NULL)
        free_graph_list(&(n->next));
    //TODO free vertices
    free(n);
    *list = NULL;
}

void add_vertex_list(graph_list* list, char* source_node, char* target_node) {

}