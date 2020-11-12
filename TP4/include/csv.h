//
// Created by hugo on 4/6/20.
//

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t parseline(char ***string_list_p, const char *line, const char separator) {
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

  *string_list_p = fields;

  return fields_index;
}

ssize_t getLine(char **lineptr, FILE *fp) {
  if (!fp)
    return -1;
  int buf;
  char *line = NULL;
  size_t length = 0;
  while ((buf = getc(fp)) != '\n') {
    if (buf == EOF)
      return -1;
    if (line)
      line = realloc(line, ++length * sizeof(char));
    else
      line = malloc(++length * sizeof(char));
    line[length - 1] = (char)buf;
  }
  *lineptr = line;
  return length;
}