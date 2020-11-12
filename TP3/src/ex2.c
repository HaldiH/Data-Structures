//
// Created by hugo on 3/21/20.
//

#include "ex2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int key_compare(const void *val1, const void *val2) {
  return *(int *)val2 - *(int *)val1;
}

map_t extractPassengerTree(const char *filename) {
  FILE *fp = fopen(filename, "r");

  if (!fp) {
    printf("%s cannot be found", filename);
    exit(EXIT_FAILURE);
  }

  int c;
  char *line = NULL;
  size_t line_size = 0;
  map_t map;
  map.begin = NULL;
  map.root = NULL;
  map.end = NULL;
  map.key_compare = key_compare;

  while ((c = getc(fp)) != EOF) {
    if (line_size == 0)
      line = malloc(++line_size * sizeof(char));
    else
      line = realloc(line, ++line_size * sizeof(char));
    if (c == '\n') {
      char **fields = getFields(line, ' ');
      passenger_t *passenger =
          passenger_factory(atoi(fields[0]), fields[1], fields[2],
                            atoi(fields[3]), atoi(fields[4]));
      map_insert(&map, make_value(passenger, &passenger->seatNumber));
      line = NULL;
      line_size = 0;
      free(fields);
    } else {
      strncat(line, (const char *)&c, 1);
    }
  }
  free(line);
  free(fp);
  return map;
}
