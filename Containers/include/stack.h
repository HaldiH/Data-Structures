//
// Created by hugo1 on 11.03.2020.
//

#ifndef CONTAINERS_STACK_H
#define CONTAINERS_STACK_H
#include "forward_list.h"
#include <stdbool.h>

typedef struct {
    ForwardList_t *list;
} Stack_t;

Stack_t *Stack_factory();
void Stack_destructor(Stack_t **stack);

void *Stack_top(Stack_t *stack);
bool Stack_empty(Stack_t *stack);
int Stack_push(Stack_t *stack, void *data);
void *Stack_pop(Stack_t *stack);
int Stack_swap(Stack_t *stack);

#endif // CONTAINERS_STACK_H
