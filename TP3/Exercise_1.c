//
// Created by hugo on 3/18/20.
//

#include "Exercise_1.h"
#include "forward_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **getFields(const char *line, const char separator) {
  char **fields = NULL;
  int fields_index = 0;
  int line_index = 0;
  for (; line[line_index] != '\0'; fields_index++) {
    if (fields_index == 0)
      fields = malloc(sizeof(char *));
    else
      fields = realloc(fields, (fields_index + 1) * sizeof(char *));
    char *field = NULL;
    for (int i = 0; line[line_index] != separator && line[line_index] != '\0';
         i++) {
      if (i == 0)
        field = malloc(sizeof(char));
      else
        field = realloc(field, (i + 1) * sizeof(char));
      strncat(field, &line[line_index++], 1);
    }
    if (line[line_index] != '\0')
      line_index++;
    fields[fields_index] = field;
  }

  return fields;
}

int main(int argc, char *argv[]) {
  const char *filename = "TP3.passagers.txt";
  FILE *fp = fopen(filename, "r");

  if (!fp) {
    printf("%s cannot be found", filename);
    return 1;
  }

  int c;
  char *line = NULL;
  size_t line_size = 0;
  ForwardList_t *list = ForwardList_factory();

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
      ForwardList_push_back(list, passenger);
      line = NULL;
      line_size = 0;
      free(fields);
    } else {
      strncat(line, (const char *)&c, 1);
    }
  }
  free(line);
  free(fp);
  while (!ForwardList_empty(list)) {
    passenger_t *passenger = ForwardList_pop_front(list);
    printf("%s\n", passenger->firstName);
  }
}