# Forward List

## Member types

| Member type                            | Definition |
| -------------------------------------- | ---------- |
| [ForwardIterator](forward_iterator.md) | begin      |
| [ForwardIterator](forward_iterator.md) | end        |

## Functions

| Function                                             | Description                 |
| ---------------------------------------------------- | --------------------------- |
| [ForwardList_factory](forward_list/factory.md)       | construct the ForwardList_t |
| [ForwardList_destructor](forward_list/destructor.md) | destructs the ForwardList_t |

### Element access

| Function                                   | Description                              |
| ------------------------------------------ | ---------------------------------------- |
| [ForwardList_front](forward_list/front.md) | access the first element                 |
| [ForwardList_back](forward_list/back.md)   | access the last element                  |
| [ForwardList_at](forward_list/at.md)       | access element at position (starts at 0) |

### Iterators

| Function                                   | Description                          |
| ------------------------------------------ | ------------------------------------ |
| [ForwardList_begin](forward_list/begin.md) | returns an iterator to the beginning |
| [ForwardList_end](forward_list/end.md)     | returns an iterator to the end       |

### Modifiers

| Function                                             | Description                                               |
| ---------------------------------------------------- | --------------------------------------------------------- |
| [ForwardList_push_front](forward_list/push_front.md) | inserts an element in-place at the beginning              |
| [ForwardList_push_back](forward_list/push_back.md)   | inserts an element in-place at the end                    |
| [ForwardList_insert](forward_list/insert.md)         | inserts an element in-place at the position (starts at 0) |
| [ForwardList_pop](forward_list/pop.md)               | removes and return the element at position (starts at 0)  |
| [ForwardList_pop_front](forward_list/pop_front.md)   | removes and return the first element                      |
| [ForwardList_pop_back](forward_list/pop_back.md)     | removes and return the last element                       |

### Operations

| Function                                 | Description        |
| ---------------------------------------- | ------------------ |
| [ForwardList_swap](forward_list/swap.md) | swaps the contents |
