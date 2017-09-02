#include "sweepLine.hpp"

int doTheSweep() {
  return 0;
}

bool comparePosition(Point_2 a,Point_2 b) {
  /**
   * Caculates and compares the position of two points in the X-axis
   */
  return (a.x() < b.x());
}

std::list<Point_2> sortByPosition(std::list<Point_2> points) {
  /**
   * Sort the given points in the list by there postion in the X-axis
   * in ascending order
   */
  points.sort(comparePosition);
  return points;
}
