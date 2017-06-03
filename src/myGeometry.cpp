#include "myGeometry.hpp"
#include "iostream"
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
  printf("slope is %f \n \n",m);
  angle = atan(m);
  printf("angle before is %f \n \n",angle);
  angle = angle * 180 / PI; // Convert Rad into degrees
  printf("angle after is %f \n \n",angle);
  return angle;
}

Line Line::getLineWithRespectTo(double angle, double length) {
  Line line;
  line.start.x_cord = this->end.x_cord;
  line.start.y_cord = this->end.y_cord;
  double angle1 = this->getInclineAngle();
  printf("angle1 is %f \n \n",angle1);
  // Here suffix 2 means that of the second line or 2nd co-ordinate of the line
  double m2 = tan(angle + angle1); // Slope of the second line.
  double x2 = sqrt((length * length) / (m2 * m2) + 1) + this->end.x_cord;
  double y2 = m2 * (x2 - this->end.x_cord) + this->end.y_cord;
  line.end.x_cord = x2;
  line.end.y_cord = y2;
  return line;
}
