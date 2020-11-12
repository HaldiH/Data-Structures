#define LINE_LENGTH 100

#include "csv.h"
#include "forward_list.h"
#include "queue.h"
#include "stack.h"
#include <stdio.h>

typedef struct {
    char *iata;
    char *city;
    char *country;
} airport_t;

typedef struct {
    bool is_discovered;
    ForwardList_t edges;
    void *data_p;
} vertex_t;

void bfs(vertex_t *v) {
    Queue_t *q = Queue_factory();
    v->is_discovered = true;
    Queue_push(q, v);
    while (!Queue_empty(q)) {
        v = Queue_pop(q);
        printf("Exploring vertex edges...\n");
        for (struct ForwardIterator *it = ForwardList_begin(&v->edges); it; it = it->next) {
            vertex_t *w = it->data;
            if (!w->is_discovered) {
                w->is_discovered = true;
                Queue_push(q, w);
            }
        }
    }
    Queue_destructor(&q);
}

void dfs(vertex_t *v) {
    Stack_t *s = Stack_factory();
    Stack_push(s, v);
    while (!Stack_empty(s)) {
        v = Stack_pop(s);
        if (!v->is_discovered) {
            for (struct ForwardIterator *it = ForwardList_begin(&v->edges); it; it = it->next) {
                vertex_t *w = it->data;
                Stack_push(s, w);
            }
        }
    }
    Stack_destructor(&s);
}

void shortest_path(vertex_t *start_v, vertex_t *goal_v) {
    // Copy of BFS
    Queue_t *q = Queue_factory();
    Stack_t *shortest_path = Stack_factory();
    Stack_push(shortest_path, start_v);
    start_v->is_discovered = true;
    Queue_push(q, start_v);
    while (!Queue_empty(q)) {
        start_v = Queue_pop(q);
        printf("Exploring vertex edges...\n");
        for (struct ForwardIterator *it = ForwardList_begin(&start_v->edges); it; it = it->next) {
            vertex_t *w = it->data;

            if (w == goal_v)

            if (!w->is_discovered) {
                w->is_discovered = true;
                Queue_push(q, w);
            }
        }
    }
    Queue_destructor(&q);
}

int main() {
    FILE *fp = fopen("aeroports.txt", "ro");
    char *line = malloc(LINE_LENGTH * sizeof(char));
    size_t length = LINE_LENGTH;
    int size;

    ForwardList_t airport_nodes_list;
    airport_nodes_list.begin = NULL;
    airport_nodes_list.end = NULL;

    while ((size = getline(&line, &length, fp)) >= 0) {
        if (line[size - 1] == '\n')
            line[size - 1] = '\0';
        char **airport = NULL;
        parseline(&airport, line, ' ');
        airport_t *airport_p = malloc(sizeof(airport_t));
        airport_p->iata = airport[0];
        airport_p->city = airport[1];
        airport_p->country = airport[2];
        vertex_t *node = malloc(sizeof(vertex_t));
        node->is_discovered = false;
        node->data_p = airport_p;
        node->edges.begin = NULL;
        node->edges.end = NULL;
        ForwardList_push_back(&airport_nodes_list, node);
    }

    fclose(fp);
    fp = fopen("liaisons.txt", "ro");

    struct ForwardIterator *current_airport_node_it = airport_nodes_list.begin;

    // Reading each line of binding
    while ((size = getline(&line, &length, fp)) >= 0) {
        vertex_t *current_airport_node = current_airport_node_it->data;

        if (line[size - 1] == '\n')
            line[size - 1] = '\0';

        char **bindings_city = NULL;
        size_t n = parseline(&bindings_city, line, ' ');

        // Making boundary for each bound
        for (int i = 0; i < n; i++) { // Making boundary for each bound
            char *binding_city = bindings_city[i];

            // Searching inside the airport list for the reached boundary;
            // we can break the loop when we found the right airport boundary.
            for (struct ForwardIterator *it = airport_nodes_list.begin; it; it = it->next) {
                vertex_t *it_airport_node = it->data;

                if (strcmp(((airport_t *)it_airport_node->data_p)->city, binding_city) == 0) {
                    ForwardList_push_back(&current_airport_node->edges, it_airport_node);
                    break;
                }
            }
        }
        current_airport_node_it = current_airport_node_it->next;
    }

    fclose(fp);

    for (struct ForwardIterator *it = ForwardList_begin(&airport_nodes_list); it; it = it->next) {
        vertex_t *airport_node = it->data;
        printf("%s is linked to the following airports:\n", ((airport_t *)airport_node->data_p)->city);
        for (struct ForwardIterator *_it = ForwardList_begin(&airport_node->edges); _it; _it = _it->next) {
            vertex_t *edge = _it->data;
            printf("%s ", ((airport_t *)edge->data_p)->city);
        }
        printf("\n\n");
    }

    bfs(airport_nodes_list.begin->data);

    return 0;
}
