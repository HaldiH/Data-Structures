//
// Created by hugo on 3/3/20.
//
#include "LinkedList.h"

struct Node *Node_factory(void *data_ptr) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->next = NULL;
    node->data = data_ptr;
    return node;
}

void Node_destructor(struct Node *to_destroy) { // WARNING ! Does not free data inside node
    free(to_destroy);
}

LinkedList *LinkedList_factory() {
    LinkedList *linkedList = (LinkedList *)malloc(sizeof(LinkedList));
    linkedList->begin = NULL;
    linkedList->end = NULL;
    return linkedList;
}

void LinkedList_destructor(LinkedList *linkedList) {
    if (!linkedList)
        return;

    while (linkedList->begin) {
        struct Node *current = linkedList->begin->next;
        Node_destructor(linkedList->begin);
        linkedList->begin = current;
    }
    free(linkedList);
}

int LinkedList_push_front(LinkedList *linked_list, void *data_ptr) {
    if (!linked_list)
        return 1;

    struct Node *node = Node_factory(data_ptr);
    node->next = linked_list->begin;
    linked_list->begin = node;
    if (!linked_list->end)
        linked_list->end = node;
    return 0;
}

int LinkedList_push_back(LinkedList *linked_list, void *data_ptr) {
    if (!linked_list)
        return 1;

    struct Node *node = Node_factory(data_ptr);
    node->next = NULL;

    if (!linked_list->end) {
        linked_list->begin = node;
        linked_list->end = node;
        return 0;
    }

    linked_list->end->next = node;
    linked_list->end = node;
    return 0;
}

int LinkedList_insert(LinkedList *linked_list, int pos, void *data_ptr) {
    if (!linked_list)
        return 1;

    if (pos == 0)
        return LinkedList_push_front(linked_list, data_ptr);

    struct Node *current = linked_list->begin;
    for (int i = 0; i < pos - 1; i++) {
        if (!current)
            return 2; // Return error code 2 if the position exceed the size of the list

        current = current->next;
    }
    struct Node *node = Node_factory(data_ptr);
    node->next = current->next;
    current->next = node;
    return 0;
}

void *LinkedList_pop(LinkedList *linked_list, int pos) {
    if (!linked_list)
        return NULL;

    if (pos == 0)
        return LinkedList_pop_front(linked_list);

    struct Node *current = linked_list->begin;
    for (int i = 0; i < pos - 1; i++) {
        if (!current)
            return NULL;
        current = current->next;
    }
    if (!current->next)
        return NULL; // If the reached value is NULL (end of the list)

    struct Node *popped_node = current->next;
    current->next = current->next->next;
    void *result = popped_node->data;
    Node_destructor(popped_node);
    return result;
}

void *LinkedList_pop_front(LinkedList *linked_list) {
    if (!linked_list || !linked_list->begin)
        return NULL;

    struct Node *popped_node = linked_list->begin;
    linked_list->begin = popped_node->next;
    void *result = popped_node->data;
    Node_destructor(popped_node);
    return result;
}

void *LinkedList_pop_back(LinkedList *linked_list) {
    if (!linked_list || !linked_list->begin)
        return NULL;

    struct Node *current = linked_list->begin;

    if (!current->next) {
        void *result = current->data;
        Node_destructor(current);
        linked_list->begin = NULL;
    }

    while (current->next->next)
        current = current->next;

    void *result = current->next->data;
    Node_destructor(current);
    current->next = NULL;
    return result;
}

int LinkedList_swap(struct Node *node1, struct Node *node2) {
    struct Node *tmp = node1;
    node1 = node2;
    node2 = tmp;
    return 0;
}

void *LinkedList_front(LinkedList *linked_list) {
    return linked_list && linked_list->begin ? linked_list->begin->data : NULL;
}

void *LinkedList_back(LinkedList *linked_list) {
    return linked_list && linked_list->end ? linked_list->end->data : NULL;
}

void *LinkedList_at(LinkedList *linked_list, int pos) {
    if (!linked_list || !linked_list->begin)
        return NULL;

    struct Node *current = linked_list->begin;
    for (int i = 0; i < pos; i++) {
        if (!current->next)
            return NULL;
        current = current->next;
    }

    return current->data;
}

struct Node *LinkedList_begin(LinkedList *linked_list) {
    return linked_list ? linked_list->begin : NULL;
}

struct Node *LinkedList_end(LinkedList *linked_list) {
    return linked_list ? linked_list->end : NULL;
}
