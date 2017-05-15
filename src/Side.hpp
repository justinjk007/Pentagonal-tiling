/**
 * This structure defines one side in the pentagon.
 *
 * A Structure is defined instead of just a value in the Tile class
 * because of the added data members like next and previous which
 * might come handy during the final operations.
 */
#ifndef SIDE_HPP
#define SIDE_HPP

struct Side {
  double value;
  Side *next;
  Side *previous;
  Side(double val, Side *nex, Side *prev) {
    this->value = val;
    this->next = nex;
    this->previous = prev;
  }
};

#endif /* SIDE_HPP */
