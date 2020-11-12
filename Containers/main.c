#include "forward_list.h"
#include "map.h"
#include "queue.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int test_comp(const void *obj1, const void *obj2) { return *((int *)obj1) - *((int *)obj2); }

int main() {
    int *test_1 = malloc(sizeof(int));
    *test_1 = 1;
    int *test_2 = malloc(sizeof(int));
    *test_2 = 2;
    int *test_3 = malloc(sizeof(int));
    *test_3 = 3;
    int *test_4 = malloc(sizeof(int));
    *test_4 = 4;

    Stack_t *container = Stack_factory();
    Stack_push(container, test_1);
    Stack_push(container, test_2);
    Stack_push(container, test_3);
    Stack_push(container, test_4);

    printf("%d\n", *((int *)Stack_pop(container)));
    printf("%d\n", *((int *)Stack_pop(container)));
    printf("%d\n", *((int *)Stack_pop(container)));
    printf("%d\n", *((int *)Stack_pop(container)));

    Stack_destructor(&container);

    map_t *map = map_factory(test_comp);
    map_insert(map, make_value("Hello", test_3));
    map_insert(map, make_value("World", test_2));
    map_insert(map, make_value("Bonjour", test_4));
    if (!map_insert(map, make_value("Monde", test_1)).b)
        printf("Monde not inserted");
    int i = 1;
    int *ptr = &i;
    const map_iterator_t *tmp = map_find(map, ptr);
    printf("%s", tmp ? tmp->value.data : "NULL");

    return 0;
}
