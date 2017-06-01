#include "myGeometry.hpp"
#include <math.h>

#define PI 3.14159265

Line Line::drawLine(Point origin, double length) {
  /**
   * This method is to draw the first line in the shape when we don't
   * have an other side for the angle to be based on
   */
  Line line ;
  line.start.x_cord = origin.x_cord;
  line.start.y_cord = origin.y_cord;
  line.end.x_cord = length;
  line.end.y_cord = 0.0;
  return line;
}

Line Line::drawLine(Point origin ,double length, double angle) {
  Line line ;
  return line;
}

double Line::getSlope() {
  double diff_y = this->end.y_cord - this->start.y_cord;
  double diff_x = this->end.x_cord - this->start.x_cord;
  double m = diff_y / diff_x;
  return m;
}

double Line::getInclineAngle() {
  double angle = 0;
  double m = this->getSlope();
  angle = atan (m) * 180 / PI; // Convert degree into Radians
  return angle;
}

double Line::getAngleWithRespectTo(Line line) {
  double angle1 = this->getInclineAngle();
  double angle2 = line.getInclineAngle();
  double diff = angle1 - angle2;
  return 0;
}


// What was the point of implementing these again ?
// you are suppose to go the other way around
