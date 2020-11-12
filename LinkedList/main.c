#include "LinkedList.h"
#include <stdio.h>

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
        printf("%i\n", (int)data);
        data = LinkedList_pop_front(list1);
    }
    printf("%i\n", (int)LinkedList_at(list2, 1));

    int *test5 = (int *)5;
    LinkedList_insert(list2, 4, test5);
    printf("%i\n", (int)LinkedList_at(list2, 4));

    return 0;
}
