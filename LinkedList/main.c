#include "LinkedList.h"
#include <stdio.h>
#include <stdint.h>

#if INTPTR_MAX == INT64_MAX
#define INTPTR_MAX_TYPE uint64_t
#elif INTPTR_MAX == INT32_MAX
#define INTPTR_MAX_TYPE uint32_t
#elif INTPTR_MAX == INT16_MAX
#define INTPTR_MAX_TYPE uint16_t
#elif INTPTR_MAX == INT8_MAX
#define INTPTR_MAX_TYPE uint8_t
#else
#error Unknown pointer size or missing size macros!
#endif

int main() {
    int *test_1 = (int *)1;
    int *test_2 = (int *)2;
    int *test_3 = (int *)3;
    int *test_4 = (int *)4;

    LinkedList *list1 = LinkedList_factory();
    LinkedList_push_back(list1, test_1);
    LinkedList_push_back(list1, test_2);
    LinkedList_push_back(list1, test_3);
    LinkedList_push_back(list1, test_4);

    LinkedList *list2 = LinkedList_factory();
    LinkedList_push_back(list2, test_1);
    LinkedList_push_back(list2, test_2);
    LinkedList_push_back(list2, test_3);
    LinkedList_push_back(list2, test_4);

    void *data = LinkedList_pop_front(list1);

    while (data) {
        printf("%lu\n", (INTPTR_MAX_TYPE)data);
        data = LinkedList_pop_front(list1);
    }
    printf("%lu\n", (INTPTR_MAX_TYPE)LinkedList_at(list2, 1));

    int *test5 = (int *)5;
    LinkedList_insert(list2, 4, test5);
    printf("%lu\n", (INTPTR_MAX_TYPE)LinkedList_at(list2, 4));

    return 0;
}
