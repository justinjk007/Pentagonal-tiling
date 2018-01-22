#ifndef MYGEOMETRY_HPP
#define MYGEOMETRY_HPP

class Point
{
   public:
    double x;
    double y;
    Point() : x(0.0), y(0.0)
    {
    }
    Point(double x_cord, double y_cord) : x(x_cord), y(y_cord)
    {
    }
};

class Line
{
   public:
    Point source;
    Point target;

    double getSlope();
    double getInclineAngle();
    double getInclineAngle(double);
    Line getLineWithRespectTo(Point, double);
    Line getLineWithRespectTo(double, double, int, char);
    Line reverse();  // Reverse the start and end points of the line.
    Line() : source(Point()), target(Point())
    {
    }
    Line(Point a, Point b) : source(a), target(b)
    {
    }
};

bool compareLine(Line, Line);

#endif /* MYGEOMETRY_HPP */
