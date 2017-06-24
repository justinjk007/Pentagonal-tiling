#include "myGeometry.hpp"
#include "iostream"
#include <math.h>

#define PI 3.14159265359

bool compareLine(Line line1, Line line2){
  /**
   * Compare lines to see if they are equal, true if they are equal else false
   */
  bool first = false, second = false;
  double diff1 = line1.start.x_cord - line2.start.x_cord;
  double diff2 = line1.end.x_cord - line2.end.x_cord;
  double diff3 = line1.start.y_cord - line2.start.y_cord;
  double diff4 = line1.end.y_cord - line2.end.y_cord;
  if (diff1 < 0.02 || diff2 < 0.02 || diff3 < 0.02 || diff4 < 0.02)
    first = true;

  diff1 = line1.start.x_cord - line2.end.x_cord;
  diff2 = line1.end.x_cord - line2.start.x_cord;
  diff3 = line1.start.y_cord - line2.end.y_cord;
  diff4 = line1.end.y_cord - line2.start.y_cord;
  if (diff1 < 0.02 || diff2 < 0.02 || diff3 < 0.02 || diff4 < 0.02)
    second = true;

  if (first || second)
    return true;
  else
    return false;
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

Line Line::reverse() {
  /**
   * Reverses the start and end points
   */
    Line temp_line;
    temp_line.start.x_cord = this->end.x_cord;
    temp_line.start.y_cord = this->end.y_cord;
    temp_line.end.x_cord = this->start.x_cord;
    temp_line.end.y_cord = this->start.y_cord;
    return temp_line;
}

Line Line::getLineWithRespectTo(Point origin, double length) {
  /**
   * This method is to draw the first line in the shape when we don't
   * have an other side for the angle to be based on
   */
  Line line;
  line.start.x_cord = origin.x_cord;
  line.start.y_cord = origin.y_cord;
  line.end.x_cord = length;
  line.end.y_cord = 0.0;
  return line;
}

Line Line::getLineWithRespectTo(double angle2, double length, int type, char which) {
  /**
   * This method is to draw the lines with respect to the angle
   * between this line & the last line and the length of the second line.
   * Here suffix 2 means that of the second line or 2nd co-ordinate of the line
   * 'which variable decides to see if we want the diagonal or the side'
   */
  static int check = 0;
  Line line;
  double m2 = 0.0;
  double x2 = 0.0;
  double y2 = 0.0;
  double m = this->getSlope();
  m2 = (tan(angle2 * 22 / 7 / 180) + m) / (1 - (tan(angle2 * 22 / 7 / 180) * m));
  std::cout << "type passed: " << type << "\n";
  if (check%2 == 0)
    std::cout << "angle passed: " << angle2 << "\n";
  else
    std::cout << "angle passed: " << 180-angle2 << "\n";
  check++;
  std::cout << "Slope of the second line: " << m2 << "\n";
  std::cout << "length of the second line: " << length << "\n";
  if (which == 's') {
    if (type == 0)
      // Type on is when x2 is greater than x1.
      x2 = this->end.x_cord + sqrt(pow(length, 2) / (1 + pow(m2, 2)));
    else
      // Type on is when x2 is smaller than x1, ie the line is backward.
      x2 = this->end.x_cord - sqrt(pow(length, 2) / (1 + pow(m2, 2)));
    y2 = m2 * (x2 - this->end.x_cord) + this->end.y_cord;
    line.start.x_cord = this->end.x_cord;
    line.start.y_cord = this->end.y_cord;
  } else if (which == 'd') // when which = 'd' for diagonal.
    {
      if (type == 0)
	// Type on is when x2 is greater than x1.
	x2 = this->start.x_cord + sqrt(pow(length, 2) / (1 + pow(m2, 2)));
      else
	// Type on is when x2 is smaller than x1, ie the line is backward.
	x2 = this->start.x_cord - sqrt(pow(length, 2) / (1 + pow(m2, 2)));
      y2 = m2 * (x2 - this->start.x_cord) + this->start.y_cord;
      line.start.x_cord = this->start.x_cord;
      line.start.y_cord = this->start.y_cord;
    } else
    return line;

  std::cout << "new co-ordinates found are "
  	    << "(" << x2 << ", " << y2 << ")"
  	    << "\n";
  line.end.x_cord = x2;
  line.end.y_cord = y2;
  return line;
}
