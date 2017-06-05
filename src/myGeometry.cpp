#include "myGeometry.hpp"
#include "iostream"
#include <math.h>

#define PI 3.14159265359

double Line::getSlope() {
  double diff_y = this->end.y_cord - this->start.y_cord;
  double diff_x = this->end.x_cord - this->start.x_cord;
  double m = diff_y / diff_x;
  return m;
}

double Line::getInclineAngle() {
  double angle = 0;
  double m = this->getSlope();
  angle = atan(m);
  angle = angle * (180 / PI); // Convert Rad into degrees
  return angle;
}

Line Line::getLineWithRespectTo(Point origin, double length) {
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

Line Line::getLineWithRespectTo(double angle2, double length) {
  /**
   * This method is to draw the lines with respect to the angle
   * between this line & the last line and the length of the second line.
   */
  Line line;
  line.start.x_cord = this->end.x_cord;
  line.start.y_cord = this->end.y_cord;
  double angle1 = this->getInclineAngle();
  // Here suffix 2 means that of the second line or 2nd co-ordinate of the line
  double m2 = tan((angle2 + angle1)*(PI/180)); // Slope of the second line.
  double x2 = sqrt(pow(length, 2) / (1 + pow(m2, 2))) + this->end.x_cord;
  double y2 = m2 * (x2 - this->end.x_cord) + this->end.y_cord;
  line.end.x_cord = x2;
  line.end.y_cord = y2;
  return line;
}
