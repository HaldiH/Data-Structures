//
// Created by hugo on 3/3/20.
//
#ifndef TP2_LINKEDLIST_H
#define TP2_LINKEDLIST_H
#include <stdlib.h>

struct Node {
    struct Node *next;
    void *data;
};

struct Node *Node_factory();
void Node_destructor(struct Node *to_destroy);

typedef struct {
    struct Node *begin;
    struct Node *end;
} LinkedList;

LinkedList *LinkedList_factory();
void LinkedList_destructor(LinkedList *linkedList);

int LinkedList_push_front(LinkedList *linked_list, void *data_ptr);
int LinkedList_push_back(LinkedList *linked_list, void *data_ptr);
int LinkedList_insert(LinkedList *linked_list, int pos, void *data_ptr);
void *LinkedList_pop(LinkedList *linked_list, int pos);
void *LinkedList_pop_front(LinkedList *linked_list);
void *LinkedList_pop_back(LinkedList *linked_list);
int LinkedList_swap(struct Node *node1, struct Node *node2);

void *LinkedList_front(LinkedList *linked_list);
void *LinkedList_back(LinkedList *linked_list);
void *LinkedList_at(LinkedList *linked_list, int pos);

struct Node *LinkedList_begin(LinkedList *linked_list);
struct Node *LinkedList_end(LinkedList *linked_list);

#endif // TP2_LINKEDLIST_H
