//
// Created by hugo1 on 11.03.2020.
//
#include "../include/queue.h"
#include <stdlib.h>

Queue_t *Queue_factory() {
    Queue_t *queue = (Queue_t *)malloc(sizeof(Queue_t));
    queue->list = ForwardList_factory();
    return queue;
}
void Queue_destructor(Queue_t **queue) {
    if (!queue)
        return;
    ForwardList_destructor(&(*queue)->list);
    free(*queue);
    *queue = NULL;
}
void *Queue_pop(Queue_t *queue) { return queue ? ForwardList_pop_front(queue->list) : NULL; }
int Queue_push(Queue_t *queue, void *data) { return queue ? ForwardList_push_back(queue->list, data) : 1; }
void *Queue_front(Queue_t *queue) { return queue ? ForwardList_front(queue->list) : NULL; }
void *Queue_back(Queue_t *queue) { return queue ? ForwardList_back(queue->list) : NULL; }
bool Queue_empty(Queue_t *queue) { return !queue || ForwardList_empty(queue->list); }
int Queue_swap(Queue_t *queue) { return queue ? ForwardList_swap(&queue->list) : 1; }
