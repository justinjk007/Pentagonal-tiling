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
  angle = angle * (180 / 22 / 7); // Convert Rad into degrees
  return angle;
}

double Line::getInclineAngle(double m) {
  double angle = 0;
  angle = atan(m);
  angle = angle * (180 / 22 / 7); // Convert Rad into degrees
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
   * Here suffix 2 means that of the second line or 2nd co-ordinate of the line
   * TODO once initial problem is fixed try printing the contents of
   * the pentagon array to see there are actually 5 line nmot just 4.
   */
  static int count=1; // Because first line is already created
  count++;
  Line line;
  double m2 = 0;
  double m = this->getSlope();
  m2 =
    (tan(angle2 * 22 / 7 / 180) + m) / (1 - (tan(angle2 * 22 / 7 / 180) * m));
  double inc_angle = this->getInclineAngle(m2);
  // m2 = tan((angle2 + inc_angle)*(PI/180)); // Slope of the second line.
  std::cout << "angle passed: " << 180-angle2 << "\n";
  // std::cout << "Incline angle: "<< inc_angle << "\n";
  std::cout << "Slope of the second line: " << m2 << "\n";
  std::cout << "length of the second line: " << length << "\n";
  double x2 = sqrt(pow(length, 2) / (1 + pow(m2, 2))) + this->end.x_cord;
  if (count >2)
    x2 = this->end.x_cord -sqrt(pow(length, 2) / (1 + pow(m2, 2)));
  double y2 = m2 * (x2 - this->end.x_cord) + this->end.y_cord;

  // double x2 = (length*(cos(inc_angle*22/7/180))) + this->end.x_cord;
  // double y2 = (length*(sin(inc_angle*22/7/180))) + this->end.y_cord;
  std::cout << "new co-ordinates found are "
            << "(" << x2 << ", " << y2 << ")"
            << "\n\n";
  line.end.x_cord = x2;
  line.end.y_cord = y2;
  line.start.x_cord = this->end.x_cord;
  line.start.y_cord = this->end.y_cord;
  return line;
}
