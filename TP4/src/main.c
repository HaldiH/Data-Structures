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

typedef struct vertex {
    bool is_discovered;
    ForwardList_t edges;
    void *data_p;
    struct vertex *prev; // Usage in shortest path algorithm
} vertex_t;

vertex_t *findAirportCity(ForwardList_t *list, const char *city) {
    for (struct ForwardIterator *it = ForwardList_begin(list); it; it = it->next) {
        vertex_t *vertex = it->data;
        if (strcmp(((airport_t *)vertex->data_p)->city, city) == 0)
            return vertex;
    }
    printf("Cannot find any airport in %s city\n", city);
    exit(1);
    return NULL;
}

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

// DFS iterative
void dfs(vertex_t *v) {
    Stack_t *s = Stack_factory();
    Stack_push(s, v);
    while (!Stack_empty(s)) {
        v = Stack_pop(s);
        printf("Exploring vertex edge...\n");
        if (!v->is_discovered) {
            v->is_discovered = true;
            for (struct ForwardIterator *it = ForwardList_begin(&v->edges); it; it = it->next) {
                vertex_t *w = it->data;
                Stack_push(s, w);
            }
        }
    }
    Stack_destructor(&s);
}

vertex_t *shortest_path(vertex_t *start_v, vertex_t *goal_v) {
    // Dijkstra algorithm
    Queue_t *q = Queue_factory();
    start_v->is_discovered = true;
    Queue_push(q, start_v);
    while (!Queue_empty(q)) {
        start_v = Queue_pop(q);
        printf("Exploring vertex edges...\n");
        for (struct ForwardIterator *it = ForwardList_begin(&start_v->edges); it; it = it->next) {
            vertex_t *w = it->data;
            if (w == goal_v) {
                w->prev = start_v;
                printf("Found!\n");
                return w;
            }
            if (!w->is_discovered) {
                w->prev = start_v;
                w->is_discovered = true;
                Queue_push(q, w);
            }
        }
    }
    Queue_destructor(&q);
    printf("No route found\n");
    exit(2);
    return NULL;
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

    // Once we ran BFS or DFS, we cannot run out of the way another DFS or BFS procedure since each procedure will set
    // every vertex as discovered. We should first set every vertex as undiscovered to achieve the next procedure.

    //    printf("Running BFS...\n");
    //    bfs(ForwardList_front(&airport_nodes_list));
    //    printf("Running DFS...\n");
    //    dfs(ForwardList_front(&airport_nodes_list));

    char buffer[50];
    printf("Calculate the shortest path between 2 airports\n"
           "First airport city (e.g. Milan): ");
    fflush(stdout);
    scanf("%[^\n]", buffer);
    fgetc(stdin);
    vertex_t *start_v = findAirportCity(&airport_nodes_list, buffer);

    printf("Last airport city (e.g. Montreal): ");
    fflush(stdout);
    scanf("%[^\n]", buffer);
    fgetc(stdin);
    vertex_t *goal_v = findAirportCity(&airport_nodes_list, buffer);

    Stack_t *shortest_path_list = Stack_factory();

    vertex_t *v;
    for (v = shortest_path(start_v, goal_v); v != start_v; v = v->prev) {
        Stack_push(shortest_path_list, v);
    }
    Stack_push(shortest_path_list, v);

    printf("The shortest path between %s and %s is:\n", ((airport_t *)start_v->data_p)->city,
           ((airport_t *)goal_v->data_p)->city);

    for (vertex_t *v = Stack_pop(shortest_path_list); v != goal_v; v = Stack_pop(shortest_path_list)) {
        printf("%s --> ", ((airport_t *)v->data_p)->city);
    }
    printf("%s\n", ((airport_t *)goal_v->data_p)->city);

    return 0;
}
