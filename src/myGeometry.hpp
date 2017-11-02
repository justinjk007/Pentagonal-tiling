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
    Point source;
    Point target;
    double getSlope();
    double getInclineAngle();
    double getInclineAngle(double);
    Line getLineWithRespectTo(Point, double);
    Line getLineWithRespectTo(double, double, int, char);
    Line reverse();  // Reverse the start and end points of the line.
    Line()
    {
        this->source.x = 0.0;
        this->source.y = 0.0;
        this->target.x = 0.0;
        this->target.y = 0.0;
    }
    Line(Point a, Point b)
    {
        this->source = a;
        this->target = b;
    }
};

template <class Point>
auto getX(Point p) -> decltype(p.x)
{
    return p.x;
}

template <class Point>
auto getY(Point p) -> decltype(p.y)
{
    return p.y;
}

bool compareLine(Line, Line);

#endif /* MYGEOMETRY_HPP */
