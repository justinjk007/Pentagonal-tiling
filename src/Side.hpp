/**
 * This structure defines one side in the pentagon.
 *
 * A Structure is defined instead of just a value in the Tile class
 * because of the added data members like next and previous which
 * might come handy during the final operations.
 */
#ifndef SIDE_HPP
#define SIDE_HPP
#include <cstddef> // This library is included so that the NULL pointer works

struct Side {
  double value;
  Side *next;
  Side *previous;
  Side() {
    this->value = 0;
    this->next = NULL;
    this->previous = NULL;
  }
  Side(double val, Side *nex, Side *prev) {
    this->value = val;
    this->next = nex;
    this->previous = prev;
  }
};

#endif /* SIDE_HPP */
