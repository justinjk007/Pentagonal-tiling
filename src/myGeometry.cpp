#include "myGeometry.hpp"
#include "iostream"
#include <cmath>

const double PI = 3.14159265359;

using namespace std;

bool compareLine(Line line1, Line line2) {
  /**
   * Compare lines to see if they are equal, returns true if they are equal else
   * false
   */

  // Compare start Point(x,y)
  double diff1 = line1.start.x - line2.start.x;
  double diff2 = line1.start.y - line2.start.y;
  // Compare end Point(x,y)
  double diff3 = line1.end.x - line2.end.x;
  double diff4 = line1.end.y - line2.end.y;
  if (abs(diff1) <= 0.04 && abs(diff2) <= 0.04 &&
      abs(diff3) <= 0.04 && abs(diff4) <= 0.04)
    return true;
  line1 = line1.reverse();       // Reverse one of the line and check again.

  // Compare start Point(x,y)
  diff1 = line1.start.x - line2.start.x;
  diff2 = line1.start.y - line2.start.y;
  // Compare end Point(x,y)
  diff3 = line1.end.x - line2.end.x;
  diff4 = line1.end.y - line2.end.y;
  if (abs(diff1) <= 0.04 && abs(diff2) <= 0.04 &&
      abs(diff3) <= 0.04 && abs(diff4) <= 0.04)
    return true;
  else
    return false;
}

double Line::getSlope() {
  double diff_y = this->end.y - this->start.y;
  double diff_x = this->end.x - this->start.x;
  double m = diff_y / diff_x;
  return m;
}

double Line::getInclineAngle() {
  double angle = 0.0;
  double m = this->getSlope();
  angle = atan(m);
  angle = angle * (180.0 / 22.0 / 7.0); // Convert Rad into degrees
  return angle;
}

double Line::getInclineAngle(double m) {
  double angle = 0.0;
  angle = atan(m);
  angle = angle * (180.0 / 22.0 / 7.0); // Convert Rad into degrees
  return angle;
}

Line Line::reverse() {
  /**
   * Reverses the start and end points
   */
    Line temp_line;
    temp_line.start.x = this->end.x;
    temp_line.start.y = this->end.y;
    temp_line.end.x = this->start.x;
    temp_line.end.y = this->start.y;
    return temp_line;
}

Line Line::getLineWithRespectTo(Point origin, double length) {
  /**
   * This method is to draw the first line in the shape when we don't
   * have an other side for the angle to be based on
   */
  Line line;
  line.start.x = origin.x;
  line.start.y = origin.y;
  line.end.x = length;
  line.end.y = 0.0;
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
  m2 = (tan(angle2 * 22.0 / 7.0 / 180.0) + m) / (1.0 - (tan(angle2 * 22.0 / 7.0 / 180.0) * m));
  check++;
  if (which == 's') {
    if (type == 0)
      // Type on is when x2 is greater than x1.
      x2 = this->end.x + sqrt(pow(length, 2.0) / (1.0 + pow(m2, 2.0)));
    else
      // Type on is when x2 is smaller than x1, ie the line is backward.
      x2 = this->end.x - sqrt(pow(length, 2.0) / (1.0 + pow(m2, 2.0)));
    y2 = m2 * (x2 - this->end.x) + this->end.y;
    line.start.x = this->end.x;
    line.start.y = this->end.y;
  } else if (which == 'd') // when which = 'd' for diagonal.
    {
      if (type == 0)
	// Type on is when x2 is greater than x1.
	x2 = this->start.x + sqrt(pow(length, 2.0) / (1.0 + pow(m2, 2.0)));
      else
	// Type on is when x2 is smaller than x1, ie the line is backward.
	x2 = this->start.x - sqrt(pow(length, 2.0) / (1.0 + pow(m2, 2.0)));
      y2 = m2 * (x2 - this->start.x) + this->start.y;
      line.start.x = this->start.x;
      line.start.y = this->start.y;
    } else
    return line;

  line.end.x = x2;
  line.end.y = y2;
  return line;
}
