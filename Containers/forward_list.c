//
// Created by hugo on 3/3/20.
//
#include "../include/forward_list.h"
#include <stdlib.h>

struct ForwardIterator *ForwardIterator_factory(void *data_ptr) {
    struct ForwardIterator *node = (struct ForwardIterator *)malloc(sizeof(struct ForwardIterator));
    node->next = NULL;
    node->data = data_ptr;
    return node;
}

void ForwardIterator_destructor(struct ForwardIterator **to_destroy) { // WARNING ! Does not free data inside node
    free(*to_destroy);
    *to_destroy = NULL;
}

ForwardList_t *ForwardList_factory() {
    ForwardList_t *ForwardList = (ForwardList_t *)malloc(sizeof(ForwardList_t));
    ForwardList->begin = NULL;
    ForwardList->end = NULL;
    return ForwardList;
}

void ForwardList_destructor(ForwardList_t **forward_list) {
    if (!forward_list)
        return;

    while ((*forward_list)->begin) {
        struct ForwardIterator *current = (*forward_list)->begin->next;
        ForwardIterator_destructor(&(*forward_list)->begin);
        (*forward_list)->begin = current;
    }
    free(*forward_list);
    *forward_list = NULL;
}

int ForwardList_push_front(ForwardList_t *forward_list, void *data_ptr) {
    if (!forward_list)
        return 1;

    struct ForwardIterator *node = ForwardIterator_factory(data_ptr);
    node->next = forward_list->begin;
    forward_list->begin = node;
    if (!forward_list->end)
        forward_list->end = node;
    return 0;
}

int ForwardList_push_back(ForwardList_t *forward_list, void *data_ptr) {
    if (!forward_list)
        return 1;

    struct ForwardIterator *node = ForwardIterator_factory(data_ptr);
    node->next = NULL;

    if (!forward_list->end) {
        forward_list->begin = node;
        forward_list->end = node;
        return 0;
    }

    forward_list->end->next = node;
    forward_list->end = node;
    return 0;
}

int ForwardList_insert(ForwardList_t *forward_list, int pos, void *data_ptr) {
    if (!forward_list)
        return 1;

    if (pos == 0)
        return ForwardList_push_front(forward_list, data_ptr);

    struct ForwardIterator *current = forward_list->begin;
    if (!current)
        return 2;
    for (int i = 0; i < pos - 1; i++) {
        if (!current)
            return 2; // Return error code 2 if the position exceed the size of the
                      // list

        current = current->next;
    }
    struct ForwardIterator *node = ForwardIterator_factory(data_ptr);
    node->next = current->next;
    current->next = node;
    return 0;
}

void *ForwardList_pop(ForwardList_t *forward_list, int pos) {
    if (!forward_list)
        return NULL;

    if (pos == 0)
        return ForwardList_pop_front(forward_list);

    struct ForwardIterator *current = forward_list->begin;
    for (int i = 0; i < pos - 1; i++) {
        if (!current)
            return NULL;
        current = current->next;
    }
    if (!current->next)
        return NULL; // If the reached value_t is NULL (end of the list)

    struct ForwardIterator *popped_node = current->next;
    current->next = current->next->next;
    void *result = popped_node->data;
    ForwardIterator_destructor(&popped_node);
    return result;
}

void *ForwardList_pop_front(ForwardList_t *forward_list) {
    if (!forward_list || !forward_list->begin)
        return NULL;

    struct ForwardIterator *popped_node = forward_list->begin;
    if (forward_list->begin == forward_list->end)
        forward_list->end = popped_node->next;
    forward_list->begin = popped_node->next;
    void *result = popped_node->data;
    ForwardIterator_destructor(&popped_node);
    return result;
}

void *ForwardList_pop_back(ForwardList_t *forward_list) {
    if (!forward_list || !forward_list->begin)
        return NULL;

    struct ForwardIterator *current = forward_list->begin;

    if (!current->next) {
        void *result = current->data;
        ForwardIterator_destructor(&current);
        forward_list->begin = NULL;
        return result;
    }

    while (current->next->next)
        current = current->next;

    void *result = current->next->data;
    ForwardIterator_destructor(&current->next);
    forward_list->end = current;
    current->next = NULL;
    return result;
}

int ForwardList_swap(ForwardList_t **list) {
    if (!list)
        return 1;
    ForwardList_t *swapped = ForwardList_factory();
    int rc = 0;
    while (!ForwardList_empty(*list) && rc == 0)
        rc = ForwardList_push_front(swapped, ForwardList_pop_front(*list));
    if (rc == 0)
        *list = swapped;
    return rc;
}

void *ForwardList_front(ForwardList_t *forward_list) {
    return forward_list && forward_list->begin ? forward_list->begin->data : NULL;
}

void *ForwardList_back(ForwardList_t *forward_list) {
    return forward_list && forward_list->end ? forward_list->end->data : NULL;
}

void *ForwardList_at(ForwardList_t *forward_list, int pos) {
    if (!forward_list || !forward_list->begin)
        return NULL;

    struct ForwardIterator *current = forward_list->begin;
    for (int i = 0; i < pos; i++) {
        if (!current->next)
            return NULL;
        current = current->next;
    }

    return current->data;
}

struct ForwardIterator *ForwardList_begin(ForwardList_t *forward_list) {
    return forward_list ? forward_list->begin : NULL;
}

struct ForwardIterator *ForwardList_end(ForwardList_t *forward_list) {
    return forward_list ? forward_list->end : NULL;
}
void *ForwardList_erase_after(ForwardList_t *forward_list, struct ForwardIterator *first,
                              struct ForwardIterator *last) {
    if (!forward_list || !first || !last)
        return NULL;

    struct ForwardIterator *current = first->next;
    while (current != last) {
        struct ForwardIterator *temp = current;
        current = current->next;
        free(temp->data);
        ForwardIterator_destructor(&temp);
    }
    last = last->next;
    free(current->data);
    ForwardIterator_destructor(&current);

    first->next = last;
    return last;
}
bool ForwardList_empty(ForwardList_t *forward_list) {
    return !forward_list || !forward_list->begin || !forward_list->end;
}
