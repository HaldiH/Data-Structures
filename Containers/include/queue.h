//
// Created by hugo1 on 11.03.2020.
//

#ifndef CONTAINERS_QUEUE_H
#define CONTAINERS_QUEUE_H

#include "forward_list.h"
#include <stdbool.h>

typedef struct {
    ForwardList_t *list;
} Queue_t;

Queue_t *Queue_factory();
void Queue_destructor(Queue_t **queue);

void *Queue_pop(Queue_t *queue);
int Queue_push(Queue_t *queue, void *data);
void *Queue_front(Queue_t *queue);
void *Queue_back(Queue_t *queue);
bool Queue_empty(Queue_t *queue);
int Queue_swap(Queue_t *queue);

#endif // CONTAINERS_QUEUE_H
