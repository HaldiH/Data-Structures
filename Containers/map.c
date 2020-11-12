//
// Created by hugo on 3/22/20.
//

#include "map.h"

pair_bool make_pair(map_iterator_t *it, bool b) {
    pair_bool p;
    p.it = it;
    p.b = b;
    return p;
}

map_iterator_t *map_iterator_factory(value_t value) {
    map_iterator_t *it = malloc(sizeof(map_iterator_t));
    it->value = value;
    it->parent = NULL;
    it->left = NULL;
    it->right = NULL;
    return it;
}
map_t *map_factory(int (*key_compare)(const void *, const void *)) {
    map_t *map = malloc(sizeof(map_t));
    map->key_compare = key_compare;
    map->root = NULL;
    map->begin = NULL;
    return map;
}
pair_bool map_insert(map_t *map, const value_t value) {
    if (!map->root)
        return make_pair(map->begin = map->root = map_iterator_factory(value), true);
    map_iterator_t *it = map->root;

    while (it) {
        int comp = map->key_compare(value.key, it->value.key);
        if (comp < 0) {
            if (!it->left) {
                it->left = map_iterator_factory(value);
                it->left->parent = it;
                if (it == map->begin)
                    map->begin = it->left;
                break;
            }
            it = it->left;
        } else if (comp > 0) {
            if (!it->right) {
                it->right = map_iterator_factory(value);
                it->right->parent = it;
                break;
            }
            it = it->right;
        } else
            return make_pair(it, false); // Appends when the key is equal to an existing one
    }
    return make_pair(it, true);
}
value_t make_value(void *data, void *key) {
    value_t value;
    value.data = data;
    value.key = key;
    return value;
}
map_iterator_t *map_begin(map_t *map) { return map->begin; }
map_iterator_t *map_find(map_t *map, const void *key) {
    map_iterator_t *it = map->root;
    while (it) {
        if (map->key_compare(key, it->value.key) == 0)
            return it;
        if (map->key_compare(key, it->value.key) < 0)
            it = it->left;
        else if (map->key_compare(key, it->value.key) > 0)
            it = it->right;
    }
    return it; // Return NULL if not found
}
