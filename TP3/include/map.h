//
// Created by hugo on 3/22/20.
//

#ifndef CONTAINERS_MAP_H
#define CONTAINERS_MAP_H
#define DEF_PAIR(name, first, second)                                          \
  typedef struct {                                                             \
    first;                                                                     \
    second;                                                                    \
  } name;

#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  void *key;
  void *data;
} value_t;

value_t make_value(void *data, void *key);

typedef struct map_iterator_t {
  value_t value;
  struct map_iterator_t *parent;
  struct map_iterator_t *left;
  struct map_iterator_t *right;
} map_iterator_t;

map_iterator_t *map_iterator_factory(value_t value);

DEF_PAIR(pair_bool, map_iterator_t *it, bool b);

typedef struct {
  map_iterator_t *begin;
  map_iterator_t *root;
  int (*key_compare)(const void *key1, const void *key2);
} map_t;

map_t *map_factory(int (*key_compare)(const void *, const void *));

pair_bool map_insert(map_t *map, value_t value);
// size_t map_erase(map_t *map, const void *key); //Not implemented yet
// map_t *map_iterator_next(map_t *it); //Not implemented yet
// map_t *map_iterator_prev(map_t *it); //Not implemented yet
map_iterator_t *map_begin(map_t *map);
map_iterator_t *map_find(map_t *map, const void *key);

#endif // CONTAINERS_MAP_H
