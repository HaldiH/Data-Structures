//
// Created by hugo on 3/3/20.
//
#pragma once

struct ForwardIterator {
    struct ForwardIterator *next;
    void *data;
};

struct ForwardIterator *ForwardIterator_factory(void *data_ptr);
void ForwardIterator_destructor(struct ForwardIterator *to_destroy);

typedef struct {
    struct ForwardIterator *begin;
    struct ForwardIterator *end;
} ForwardList_t;

ForwardList_t *ForwardList_factory();
void ForwardList_destructor(ForwardList_t *forward_list);

int ForwardList_push_front(ForwardList_t *forward_list, void *data_ptr);
int ForwardList_push_back(ForwardList_t *forward_list, void *data_ptr);
int ForwardList_insert(ForwardList_t *forward_list, int pos, void *data_ptr);
void *ForwardList_pop(ForwardList_t *forward_list, int pos);
void *ForwardList_pop_front(ForwardList_t *forward_list);
void *ForwardList_pop_back(ForwardList_t *forward_list);
int ForwardList_swap(struct ForwardIterator **iterator1, struct ForwardIterator **iterator2);
void *ForwardList_erase_after(ForwardList_t *forward_list, struct ForwardIterator *first, struct ForwardIterator *last);

void *ForwardList_front(ForwardList_t *forward_list);
void *ForwardList_back(ForwardList_t *forward_list);
void *ForwardList_at(ForwardList_t *forward_list, int pos);

struct ForwardIterator *ForwardList_begin(ForwardList_t *forward_list);
struct ForwardIterator *ForwardList_end(ForwardList_t *forward_list);
