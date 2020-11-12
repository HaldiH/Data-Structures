//
// Created by hugo on 3/25/20.
//
#include "ex1.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  ForwardList_t list = extractPassengerList("TP3.passagers.txt");

  while (!ForwardList_empty(&list)) {
    passenger_t *passenger = ForwardList_pop_front(&list);
    printf("%s\n", passenger->firstName);
  }
}