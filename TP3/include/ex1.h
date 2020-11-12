//
// Created by hugo on 3/18/20.
//

#ifndef TP3_EXERCISE_1_H
#define TP3_EXERCISE_1_H

#include "forward_list.h"
#include <stdlib.h>

typedef unsigned int uint;

typedef struct {
  uint id;
  char *firstName;
  char *lastName;
  uint age;
  uint seatNumber;
} passenger_t;

passenger_t *passenger_factory(uint id, char *firstName, char *lastName,
                               uint age, uint seatNumber);

char **getFields(const char *line, char separator);

ForwardList_t extractPassengerList(const char *filename);

#endif // TP3_EXERCISE_1_H
