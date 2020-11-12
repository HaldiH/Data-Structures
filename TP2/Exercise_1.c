//
// Created by hugo1 on 11.03.2020.
//
#include "Exercise_1.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

task_t *task_factory(char *task_name) {
    task_t *task = malloc(sizeof(task_t));
    task->isOk = false;
    task->task_name = task_name;
    return task;
}

sub_cat_t *sub_cat_factory(char *sub_category_name) {
    sub_cat_t *subCat = malloc(sizeof(sub_cat_t));
    subCat->isOk = false;
    subCat->sub_cat_name = sub_category_name;
    subCat->task_stack = Stack_factory();
    return subCat;
}

category_t *category_factory(char *category_name) {
    category_t *category = malloc(sizeof(category_t));
    category->isOk = false;
    category->category_name = category_name;
    category->sub_category_stack = Stack_factory();
    return category;
}
Stack_t *getTaskStack(sub_cat_t *subCategory) { return subCategory ? subCategory->task_stack : NULL; }
Stack_t *getSubCategoryStack(category_t *category) { return category ? category->sub_category_stack :NULL; }
category_t *getTopCategory(Stack_t *categoryStack) { return Stack_top(categoryStack); }
sub_cat_t *getTopSubCategory(Stack_t *subCategoryStack) { return Stack_top(subCategoryStack); }
task_t *getTopTask(Stack_t *taskStack) { return Stack_top(taskStack); }

instruction_t getInstruction(const char *line) {
    char currentChar;
    instruction_t instruction;
    instruction.status = NULL;
    instruction.action = NULL;
    int i;
    for (i = 0; (currentChar = line[i]) != ',' && currentChar != '\n' && currentChar != '\0'; i++) {
        if (i == 0)
            instruction.status = malloc(sizeof(char));
        else
            instruction.status = realloc(instruction.status, (i + 1) * sizeof(char));
        instruction.status[i] = currentChar;
    }
    for (int j = ++i; (currentChar = line[i]) != '\n' && currentChar != '\0'; i++) {
        if (i - j == 0)
            instruction.action = malloc(sizeof(char));
        else
            instruction.action = realloc(instruction.action, (i - j + 1) * sizeof(char));
        instruction.action[i - j] = currentChar;
    }
    return instruction;
}

int main(int argc, char *argv[]) {
    char *filename = "checklist_TP2.txt";
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Could not open file %s", filename);
        return 1;
    }
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    instruction_type_t instructionType;

    Stack_t *categoryStack = Stack_factory();

    while ((read = getline(&line, &len, fp)) != -1) {
        instruction_t instruction = getInstruction(line);
        if (!instruction.status)
            continue;
        if (strcmp(instruction.status, "categorie") == 0) {
            Stack_push(categoryStack, category_factory(instruction.action));
        } else if (strcmp(instruction.status, "sous-categorie") == 0) {
            Stack_push(getSubCategoryStack(getTopCategory(categoryStack)), sub_cat_factory(instruction.action));
        } else if (strcmp(instruction.status, "tache") == 0) {
            Stack_push(getTaskStack(getTopSubCategory(getSubCategoryStack(getTopCategory(categoryStack)))),
                       task_factory(instruction.action));
        }
    }
    fclose(fp);
    free(line);

    while (!Stack_empty(categoryStack)) {
        category_t *category = Stack_pop(categoryStack);
        printf("\n%s\n", (category->category_name));
        while (!Stack_empty(category->sub_category_stack)) {
            sub_cat_t *subCat = Stack_pop(category->sub_category_stack);
            printf("\n%s\n", subCat->sub_cat_name);
            while (!Stack_empty(subCat->task_stack)) {
                task_t *task = Stack_pop(subCat->task_stack);
                printf("%s ", task->task_name);
            }
        }
    }
}
