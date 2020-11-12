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

map_iterator_t *map_iterator_factory(value_t);
void map_iterator_destructor(map_iterator_t **it);
value_t map_iterator_getValue(map_iterator_t *);

DEF_PAIR(pair_bool, map_iterator_t *it, bool b);

typedef struct {
  map_iterator_t *begin;
  map_iterator_t *root;
  map_iterator_t *end;
  int (*key_compare)(const void *key1, const void *key2);
} map_t;

map_t *map_factory(int (*key_compare)(const void *, const void *));
void map_destructor(map_t **);
pair_bool map_insert(map_t *, value_t);
// size_t map_erase(map_t *map, const void *key); //Not implemented yet
map_iterator_t *map_iterator_next(map_iterator_t *); // Not implemented yet
// map_t *map_iterator_prev(map_t *it); //Not implemented yet
map_iterator_t *map_begin(map_t *);
map_iterator_t *map_end(map_t *);
map_iterator_t *map_find(map_t *, const void *key);

#endif // CONTAINERS_MAP_H
