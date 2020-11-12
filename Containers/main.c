#include "forward_list.h"
#include "stack.h"
#include "queue.h"
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

    /*ForwardList_t *list1 = ForwardList_factory();
     ForwardList_push_back(list1, test_1);
     ForwardList_push_back(list1, test_2);
     ForwardList_push_back(list1, test_3);
     ForwardList_push_back(list1, test_4);
     ForwardList_erase_after(list1, ForwardList_begin(list1), ForwardList_end(list1));
     int *data;
     while ((data = ForwardList_pop_back(list1))) {
         printf("%d\n", *data);
     }*/

    Queue_t *container = Queue_factory();
    Queue_push(container, test_1);
    Queue_push(container, test_2);
    Queue_push(container, test_3);
    Queue_push(container, test_4);

    while (!Queue_empty(container))
        printf("%d\n", *((int*)Queue_pop(container)));

    return 0;
}
