#ifndef MYGEOMETRY_HPP
#define MYGEOMETRY_HPP

class Point
{
   public:
    double x;
    double y;
    Point()
    {
        this->x = 0.0;
        this->y = 0.0;
    }
    Point(double x_cord, double y_cord)
    {
        this->x = x_cord;
        this->y = y_cord;
    }
};

class Line
{
   public:
    Point start;
    Point end;
    double getSlope();
    double getInclineAngle();
    double getInclineAngle(double);
    Line getLineWithRespectTo(Point, double);
    Line getLineWithRespectTo(double, double, int, char);
    Line reverse();  // Reverse the start and end points of the line.
    Line()
    {
        this->start.x = 0.0;
        this->start.y = 0.0;
        this->end.x   = 0.0;
        this->end.y   = 0.0;
    }
    Line(Point a, Point b)
    {
        this->start = a;
        this->end   = b;
    }
};

bool compareLine(Line, Line);

#endif /* MYGEOMETRY_HPP */
