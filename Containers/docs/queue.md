# Queue

## Member types

| Member type                      | Definition |
| -------------------------------- | ---------- |
| [ForwardList_t](forward_list.md) | list       |

## Functions

| Member functions | Description          |
| ---------------- | -------------------- |
| Queue_factory    | constructs the queue |
| Queue_destructor | destructs the queue  |

### Element access

| Member functions | Description              |
| ---------------- | ------------------------ |
| Queue_front      | access the first element |
| Queue_back       | access the last element  |

### Capacity

| Member functions | Description                                      |
| ---------------- | ------------------------------------------------ |
| Queue_empty      | checks whether the underlying container is empty |

### Modifiers

| Member functions | Description                           |
| ---------------- | ------------------------------------- |
| Queue_push       | inserts element in-place at the front |
| Queue_pop        | removes the last element              |
| Queue_swap       | swap the contents                     |
