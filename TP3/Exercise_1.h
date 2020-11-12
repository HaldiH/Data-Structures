//
// Created by hugo on 3/18/20.
//

#ifndef TP3_EXERCISE_1_H
#define TP3_EXERCISE_1_H

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
                               uint age, uint seatNumber) {
  passenger_t *passenger = malloc(sizeof(passenger_t));
  passenger->id = id;
  passenger->firstName = firstName;
  passenger->lastName = lastName;
  passenger->age = age;
  passenger->seatNumber = seatNumber;
  return passenger;
}

#endif // TP3_EXERCISE_1_H
