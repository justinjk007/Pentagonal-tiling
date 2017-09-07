#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <cstddef> // This library is included so that the NULL pointer works
#include "myGeometry.hpp"

struct Square {
  double side;
  Point point[4] = {{0.0,0.0}}; 	// Initialize x and y to 0
  Square() {
    this->side = 0.0;
  }
  Square(double side_length) {
    this->side = side_length;
  }
};

#endif /* SQUARE_HPP */
