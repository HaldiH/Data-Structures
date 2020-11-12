//
// Created by hugo1 on 11.03.2020.
//

#ifndef TP2_EXERCISE_1_H
#define TP2_EXERCISE_1_H
#include <stdbool.h>
#include <stdlib.h>
#include "stack.h"

typedef struct {
  char **task_name;
  bool isOk;
} task_t;

typedef struct {
  char **sub_cat_name;
  bool isOk;
  Stack_t *tasks;
} sub_cat_t;

typedef struct {
  char **category_name;
  bool isOk;
  Stack_t *sub_categories;
} category_t;

typedef struct {
  char *status;
  char *action;
} instruction_t;

typedef enum {CATEGORY, SUB_CATEGORY, TASK} instruction_type_t;

task_t *task_factory(char *task_name);

sub_cat_t *sub_cat_factory(char *sub_category_name);

category_t *category_factory(char *category_name);
#endif // TP2_EXERCISE_1_H
