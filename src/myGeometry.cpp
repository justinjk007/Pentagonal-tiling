#include "myGeometry.hpp"
#include <cmath>
#include <iostream>

const double PI = 3.14159265358979323846264338327950288;

using namespace std;

bool compareLine(Line line1, Line line2)
{
    /**
     * Compare lines to see if they are equal, returns true if they are equal else
     * false
     */

    // Compare start Point(x,y)
    double diff1 = line1.source.x - line2.source.x;
    double diff2 = line1.source.y - line2.source.y;
    // Compare end Point(x,y)
    double diff3 = line1.target.x - line2.target.x;
    double diff4 = line1.target.y - line2.target.y;
    if (abs(diff1) <= 0.04 && abs(diff2) <= 0.04 && abs(diff3) <= 0.04 && abs(diff4) <= 0.04)
        return true;
    line1 = line1.reverse();  // Reverse one of the line and check again.

    // Compare start Point(x,y)
    diff1 = line1.source.x - line2.source.x;
    diff2 = line1.source.y - line2.source.y;
    // Compare end Point(x,y)
    diff3 = line1.target.x - line2.target.x;
    diff4 = line1.target.y - line2.target.y;
    if (abs(diff1) <= 0.04 && abs(diff2) <= 0.04 && abs(diff3) <= 0.04 && abs(diff4) <= 0.04)
        return true;
    else
        return false;
}

double Line::getSlope()
{
    double diff_y = this->target.y - this->source.y;
    double diff_x = this->target.x - this->source.x;
    double m      = diff_y / diff_x;
    return m;
}

double Line::getInclineAngle()
{
    double angle = 0.0;
    double m     = this->getSlope();
    angle        = atan(m);
    angle        = angle * (180.0 / 22.0 / 7.0);  // Convert Rad into degrees
    return angle;
}

double Line::getInclineAngle(double m)
{
    double angle = 0.0;
    angle        = atan(m);
    angle        = angle * (180.0 / 22.0 / 7.0);  // Convert Rad into degrees
    return angle;
}

Line Line::reverse()
{
    /**
     * Reverses the start and end points
     */
    Line temp_line;
    temp_line.source.x = this->target.x;
    temp_line.source.y = this->target.y;
    temp_line.target.x = this->source.x;
    temp_line.target.y = this->source.y;
    return temp_line;
}

Line Line::getLineWithRespectTo(Point origin, double length)
{
    /**
     * This method is to draw the first line in the shape when we don't
     * have an other side for the angle to be based on
     */
    Line line;
    line.source.x = origin.x;
    line.source.y = origin.y;
    line.target.x = length;
    line.target.y = 0.0;
    return line;
}

Line Line::getLineWithRespectTo(double angle2, double length, int type, char which)
{
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
    double m  = this->getSlope();
    m2 = (tan(angle2 * 22.0 / 7.0 / 180.0) + m) / (1.0 - (tan(angle2 * 22.0 / 7.0 / 180.0) * m));
    check++;
    if (which == 's') {
        if (type == 0)
            // Type on is when x2 is greater than x1.
            x2 = this->target.x + sqrt(pow(length, 2.0) / (1.0 + pow(m2, 2.0)));
        else
            // Type on is when x2 is smaller than x1, ie the line is backward.
            x2        = this->target.x - sqrt(pow(length, 2.0) / (1.0 + pow(m2, 2.0)));
        y2            = m2 * (x2 - this->target.x) + this->target.y;
        line.source.x = this->target.x;
        line.source.y = this->target.y;
    } else if (which == 'd')  // when which = 'd' for diagonal.
    {
        if (type == 0)
            // Type on is when x2 is greater than x1.
            x2 = this->source.x + sqrt(pow(length, 2.0) / (1.0 + pow(m2, 2.0)));
        else
            // Type on is when x2 is smaller than x1, ie the line is backward.
            x2        = this->source.x - sqrt(pow(length, 2.0) / (1.0 + pow(m2, 2.0)));
        y2            = m2 * (x2 - this->source.x) + this->source.y;
        line.source.x = this->source.x;
        line.source.y = this->source.y;
    } else
        return line;

    line.target.x = x2;
    line.target.y = y2;
    return line;
}
