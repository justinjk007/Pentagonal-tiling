#ifndef HULLFINDER_H
#define HULLFINDER_H

#include <list>
#include <map>
#include <math.h>
#include <vector>

using namespace std;

class Point {
public:
  double x;
  double y;
  Point();
  Point(double _x, double _y);
  Point &operator=(const Point &other);
  Point operator+(const Point &other) const;
  Point operator-(const Point &other) const;
  Point operator*(double k) const;
  Point operator/(double k) const;
  bool operator==(const Point &other) const;
  double DotProduct(const Point &other) const;
  double DistanceSquared(const Point &to) const;
  double Distance(const Point &to) const;
  double Distance(const Point &segmentStart, const Point &segmentEnd) const;
  double DecisionDistance(const list<Point> &points) const;
};

class HullFinder {
public:
  HullFinder();
  static double IsLeft(Point p0, Point p1, Point p2);
  static bool IsPointInsidePolygon(Point v, const vector<Point> &polygon);
  static bool CheckEdgeIntersection(const Point &p1, const Point &p2,
                                    const Point &p3, const Point &p4);
  static bool CheckEdgeIntersection(const vector<Point> &hull,
                                    Point curEdgeStart, Point curEdgeEnd,
                                    Point checkEdgeStart, Point checkEdgeEnd);
  static Point NearestInnerPoint(Point edgeStart, Point edgeEnd,
                                 const vector<Point> &points,
                                 const vector<Point> &hull, bool *found);
  static vector<Point> FindConvexHull(const vector<Point> &points);
  static vector<Point> FindConcaveHull(const vector<Point> &points, double N);
};

#endif // HULLFINDER_H
