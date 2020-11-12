//
// Created by hugo1 on 11.03.2020.
//
#include "stack.h"
#include <stdlib.h>

Stack_t *Stack_factory() {
    Stack_t *stack = (Stack_t *)malloc(sizeof(Stack_t));
    stack->list = ForwardList_factory();
    return stack;
}
void Stack_destructor(Stack_t **stack) {
    if (!stack)
        return;
    ForwardList_destructor((*stack)->list);
    free(*stack);
    *stack = NULL;
}
void *Stack_top(Stack_t *stack) { return stack ? ForwardList_front(stack->list) : NULL; }
bool Stack_empty(Stack_t *stack) { return !stack || ForwardList_empty(stack->list); }
int Stack_push(Stack_t *stack, void *data) { return stack ? ForwardList_push_front(stack->list, data) : 1; }
void *Stack_pop(Stack_t *stack) { return stack ? ForwardList_pop_front(stack->list) : NULL; }
int Stack_swap(Stack_t *stack) { return stack ? ForwardList_swap(&stack->list) : 1; }
