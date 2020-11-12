//
// Created by hugo1 on 11.03.2020.
//
#include "Exercise_1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

task_t task_factory(char *task_name) {
    task_t task;
    task.task_name = task_name;
    return task;
}

sub_cat_t sub_cat_factory(char *sub_category_name) {
    sub_cat_t subCat;
    subCat.isOk = false;
    subCat.sub_cat_name = sub_category_name;
    subCat.tasks = NULL;
    subCat.tasks_size = 0;
    return subCat;
}

category_t category_factory(char *category_name) {
    category_t category;
    category.category_name = category_name;
    category.sub_categories = NULL;
    category.sub_categories_size = 0;
    return category;
}
/*Stack_t *getTaskStack(sub_cat_t *subCategory) { return subCategory ? subCategory->task_stack : NULL; }
Stack_t *getSubCategoryStack(category_t *category) { return category ? category->sub_category_stack : NULL; }
category_t *getTopCategory(Stack_t *categoryStack) { return Stack_top(categoryStack); }
sub_cat_t *getTopSubCategory(Stack_t *subCategoryStack) { return Stack_top(subCategoryStack); }
task_t *getTopTask(Stack_t *taskStack) { return Stack_top(taskStack); }*/

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

    category_t *categories = NULL;
    size_t categories_size = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        instruction_t instruction = getInstruction(line);
        if (!instruction.status)
            continue;
        if (strcmp(instruction.status, "categorie") == 0) {
            categories_size++;
            if (!categories)
                categories = malloc(sizeof(category_t));
            else
                categories = realloc(categories, categories_size * sizeof(category_t));
            categories[categories_size - 1] = category_factory(instruction.action);
        } else {
            category_t *category = &categories[categories_size - 1];
            if (strcmp(instruction.status, "sous-categorie") == 0) {
                category->sub_categories_size++;
                if (!category->sub_categories)
                    category->sub_categories = malloc(sizeof(sub_cat_t));
                else {
                    category->sub_categories =
                        realloc(category->sub_categories, category->sub_categories_size * sizeof(sub_cat_t));
                }
                category->sub_categories[category->sub_categories_size - 1] = sub_cat_factory(instruction.action);
            } else if (strcmp(instruction.status, "tache") == 0) {
                sub_cat_t *sub_category = &category->sub_categories[category->sub_categories_size - 1];
                sub_category->tasks_size++;
                if (!sub_category->tasks)
                    sub_category->tasks = malloc(sizeof(task_t));
                else
                    sub_category->tasks = realloc(sub_category->tasks, sub_category->tasks_size * sizeof(task_t));
                sub_category->tasks[sub_category->tasks_size - 1] = task_factory(instruction.action);
            }
        }
    }
    fclose(fp);
    free(line);

    for (int i = 0; i < categories_size; i++) {
        category_t *category = &categories[i];
        printf("| Categorie | %s |\n", category->category_name);
        for (int j = 0; j < category->sub_categories_size; j++) {
            sub_cat_t *sub_category = &category->sub_categories[j];
            sub_category->isOk = true;
            printf("| Sous-categorie | %s |\n", sub_category->sub_cat_name);
            for (int k = 0; k < sub_category->tasks_size; k++) {
                task_t *task = &sub_category->tasks[k];
                printf("| Tache | %s | ", task->task_name);
                char *input = malloc(100 * sizeof(char));
                fgets(input, 100, stdin);
                if (strcmp(input, "OK\n") != 0 || !sub_category->isOk)
                    sub_category->isOk = false;
            }
            if (sub_category->isOk)
                free(sub_category->tasks);
            else
                j--;
        }
        free(category->sub_categories);
    }
    free(categories);
}
