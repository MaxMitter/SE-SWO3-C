#include "./graph_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void print_edge_list(list* edge_list) {
    list list_iterator = *edge_list;
    while (list_iterator != NULL) {
        printf("%s -> ", list_iterator->value);
        list_iterator = list_iterator->next;
    }
}

void print_graph_list(graph_list *list) {
    printf("Printing Graph List:\n");
    graph_list list_iterator = *list;
    while (list_iterator != NULL) {
        printf("'%s' | V: ", list_iterator->value);

        print_edge_list(&(list_iterator->edge_list));
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
    node->edge_list = NULL;
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

bool node_in_graph_list(graph_list *list, char *value) {
    graph_list node_iterator = *list;
    while (node_iterator != NULL) {
        if (!strcmp(node_iterator->value, value)) {
            return true;
        }
        node_iterator = node_iterator->next;
    }
    return false;
}

void add_node_to_graph_list(graph_list *list, char *value) {
    if (!node_in_graph_list(list, value))
        append_list(list, new_node_list(value));
    else
        printf("Node '%s' already in graph!\n", value);
}

void remove_edge_from_list(list* edge_list, char* value) {
    list list_iterator = *edge_list;
    list_element *prev = NULL;
    while (list_iterator != NULL) {
        if (!strcmp(list_iterator->value, value))
            break;
        prev = list_iterator;
        list_iterator = list_iterator->next;
    }

    if (list_iterator != NULL) {
        if (prev != NULL)
            prev->next = list_iterator->next;
        else
            *edge_list = list_iterator->next;
    }

    free(list_iterator);
}

graph_list_element* get_node(graph_list *graph, char* value) {
    if (*graph == NULL) {
        graph_list list_iterator = *graph;
        while (list_iterator != NULL) {
            if (!strcmp(list_iterator->value, value))
                break;

            list_iterator = list_iterator->next;
        }

        if (list_iterator != NULL) {
            return list_iterator;
        }
    }
}

void remove_edge_list(graph_list* graph, char* source_node, char* target_node) {
    if (!strcmp(source_node, target_node)){
        printf("Source Node and Target Node have to be different!\n");
        return;
    }
    
    if (!node_in_graph_list(graph, source_node)) {
        printf("Source Node '%s' does not exist!", source_node);
    } else {
        if (!node_in_graph_list(graph, target_node)) {
            printf("Target Node '%s' does not exist!", target_node);
        } else {
            if (edge_in_node_list(&((*graph)->edge_list), target_node)) {
                graph_list_element *node = get_node(graph, source_node);
                remove_edge_from_list(&(node->edge_list), target_node);
            }
            else
                printf("edge '%s -> %s' does not exist.", source_node, target_node);
        }
    }
}

void remove_node_from_graph_list(graph_list* list, char* value) {
    if (node_in_graph_list(list, value)) {
        graph_list list_iterator = *list;
        graph_list_element *prev = NULL;
        while (list_iterator != NULL) {
            if(!strcmp(list_iterator->value, value))
                break;

            if (list_iterator->edge_list != NULL) {
                if (edge_in_node_list(&(list_iterator->edge_list), value)) {
                    remove_edge_from_list(&(list_iterator->edge_list), value);
                }
            }

            prev = list_iterator;
            list_iterator = list_iterator->next;
        }

        if (list_iterator != NULL) {
            if (prev != NULL)
                prev->next = list_iterator->next;
            else
                *list = list_iterator->next;
            
            if (list_iterator->edge_list != NULL)
                free_edge_list(&(list_iterator->edge_list));
            free(list_iterator);
        }
    } else
        printf("Node '%s' could not be removed: Node not found!", value);
}

void free_edge_list(list* edge_list) {
    if (*edge_list != NULL) {
        list n = *edge_list;
        if (n->next != NULL)
            free_edge_list(&(n->next));
        free(n);
        *edge_list = NULL;
    }
}

void free_graph_list(graph_list *list) {
    graph_list n = *list;
    if (n->next != NULL)
        free_graph_list(&(n->next));

    free_edge_list(&(n->edge_list));
    free(n);
    *list = NULL;
}

list_element* new_edge_list(char* target) {
    list_element *node = malloc(sizeof(list_element));
    if (node == NULL) {
        printf("Memory allocation error while adding edge '%s', aborting.", target);
        exit;
    }
    node->value = malloc((strlen(target) + 1) * sizeof(char));
    strcpy(node->value, target);
    node->next = NULL;
    return node;
}

bool edge_in_node_list(list* edge_list, char* target) {
    if (edge_list != NULL) {
        list list_iterator = *edge_list;
        while (list_iterator != NULL) {
            if (!strcmp(list_iterator->value, target))
                return true;
            list_iterator = list_iterator->next;
        }
    }
    return false;
}

void append_edge_list(list* edge_list, list_element* node) {
    if (edge_list == NULL) {
        edge_list = node;
    }
    list list_iterator = *edge_list;
    if (list_iterator == NULL)
        *edge_list = node;
    else {
        while (list_iterator->next != NULL)
            list_iterator = list_iterator->next;
        
        list_iterator->next = node;
    }
}

void add_edge_list(graph_list* list, char* source_node, char* target_node) {
    if (!strcmp(source_node, target_node)){
        printf("Source Node and Target Node have to be different!\n");
        return;
    }
    
    if (!node_in_graph_list(list, source_node)) {
        printf("Source Node '%s' does not exist!", source_node);
    } else {
        if (!node_in_graph_list(list, target_node)) {
            printf("Target Node '%s' does not exist!", target_node);
        } else {
            if (!edge_in_node_list(&((*list)->edge_list), target_node)) {
                graph_list_element *node = get_node(list, source_node);
                append_edge_list(&(node->edge_list), new_edge_list(target_node));
            }
            else
                printf("edge '%s -> %s' already exists.", source_node, target_node);
        }
    }
}