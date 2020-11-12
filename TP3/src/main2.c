//
// Created by hugo on 3/25/20.
//

#include "ex2.h"
#include <stdio.h>
int main(int argc, char *argv[]) {
  map_t map = extractPassengerTree("TP3.passagers.txt");
  int i = 37;
  map_iterator_t *tmp = map_find(&map, &i);
  passenger_t *passenger = (tmp ? map_iterator_getValue(tmp).data : NULL);
  printf("%s", passenger ? passenger->firstName : "NULL\n");
}