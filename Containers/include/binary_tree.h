//
// Created by hugo on 3/22/20.
//

#ifndef CONTAINERS_BINARY_TREE_H
#define CONTAINERS_BINARY_TREE_H

struct binary_tree_t {
    void *data;
    void *key_value;
    struct binary_tree_t *left;
    struct binary_tree_t *right;
    bool (*comp)(const)
};

#endif // CONTAINERS_BINARY_TREE_H
