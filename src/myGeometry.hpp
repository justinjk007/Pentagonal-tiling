#ifndef MYGEOMETRY_HPP
#define MYGEOMETRY_HPP

class Point {
public:
  double x_cord;
  double y_cord;
  Point() {
    this->x_cord = 0.0 ;
    this->y_cord = 0.0 ;
  }
  Point(double x, double y) {
    this->x_cord = x;
    this->y_cord = y;
  }
};

#endif /* MYGEOMETRY_HPP */
