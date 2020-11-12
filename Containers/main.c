#include "forward_list.h"
#include "queue.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

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

    return 0;
}
