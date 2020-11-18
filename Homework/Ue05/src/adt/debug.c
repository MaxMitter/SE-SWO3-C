#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <string.h>

#define bool int
#define true 1
#define false 0

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

void init_graph_list(graph_list *list) {
    *list = NULL;
}

void print_vertex_list(list* vertex_list) {
    list list_iterator = *vertex_list;
    while (list_iterator != NULL) {
        printf("%s -> ", list_iterator->value);
        list_iterator = list_iterator->next;
    }
}

void print_graph_list(graph_list *list){
    printf("Printing Graph List:\n");
    graph_list list_iterator = *list;
    while (list_iterator != NULL) {
        printf("'%s' | V: ", list_iterator->value);

        print_vertex_list(&(list_iterator->vertex_list));
        printf("\n");
        list_iterator = list_iterator->next;
    }
}

graph_list_element* new_node(char *value) {
    graph_list_element *node = malloc(sizeof(graph_list_element));
    if (node == NULL) {
        printf("Memory allocation error at /add_graph_node_list/ | value: %s", value);
        exit;
    }
    node->value = malloc(strlen(value) * sizeof(char));
    node->value = value;
    node->vertex_list = NULL;
    node->next = NULL;
    return node;
}

void append (graph_list* list, graph_list_element* node) {
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
    printf("Hello from add_graph_node_list\n");
    
    if (!node_in_graph(list, value))
        append(list, new_node(value));
    else
        printf("Node already in graph!\n");
}

void free_vertex_list(list* vertex_list) {
    if (*vertex_list != NULL) {
        list n = *vertex_list;
        if (n->next != NULL)
            free_vertex_list(&(n->next));
        free(n);
        *vertex_list = NULL;
    }
}

void free_graph_list(graph_list *list) {
    graph_list n = *list;
    if (n->next != NULL)
        free_graph_list(&(n->next));
    free_vertex_list(&(n->vertex_list));
    free(n);
    *list = NULL;
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

list_element* new_vertex_list(char* target) {
    list_element *node = malloc(sizeof(list_element));
    if (node == NULL) {
        printf("Memory allocation error while adding Vertex '%s', aborting.", target);
        exit;
    }
    node->value = malloc(strlen(target) * sizeof(char));
    node->value = target;
    node->next = NULL;
    return node;
}

bool vertex_in_node(list* vertex_list, char* target) {
    if (vertex_list != NULL) {
        list list_iterator = *vertex_list;
        while (list_iterator != NULL) {
            if (!strcmp(list_iterator->value, target))
                return true;
            list_iterator = list_iterator->next;
        }
    }
    return false;
}

void append_vertex_list(list* vertex_list, list_element* node) {
    list list_iterator = *vertex_list;
    if (list_iterator == NULL)
        *vertex_list = node;
    else {
        while (list_iterator->next != NULL)
            list_iterator = list_iterator->next;
        
        list_iterator->next = node;
    }
}

void add_vertex_list(graph_list* list, char* source_node, char* target_node) {
    if (!node_in_graph(list, source_node)) {
        printf("Source Node '%s' does not exist!", source_node);
    } else {
        if (!node_in_graph(list, target_node)) {
            printf("Target Node '%s' does not exist!", target_node);
        } else {
            if (!vertex_in_node(&((*list)->vertex_list), target_node))
                append_vertex_list(&((*list)->vertex_list), new_vertex_list(target_node));
            else
                printf("Vertex '%s -> %s' already exists.", source_node, target_node);
        }
    }
}

int main(int argc, char const *argv[])
{
    graph_list g;
    init_graph_list(&g);
    add_graph_node_list(&g, "Test1\0");
    add_graph_node_list(&g, "Test2\0");
    add_graph_node_list(&g, "Test3\0");
    add_graph_node_list(&g, "Test4\0");
    print_graph_list(&g);
    add_vertex_list(&g, "Test1\0", "Test2\0");
    add_vertex_list(&g, "Test1\0", "Test4\0");

    print_graph_list(&g);
    free_graph_list(&g);
    return 0;
}
