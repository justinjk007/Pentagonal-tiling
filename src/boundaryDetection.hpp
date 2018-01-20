#ifndef BOUNDARYDETECTION_HPP
#define BOUNDARYDETECTION_HPP

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include "PrimitiveTile.hpp"
#include "cgal.hpp"
#include <vector>
#include "Side.hpp"
#include "Tile.hpp"
#include "myGeometry.hpp"

static Point_2 centroid;

Rect getBoundingBox(const std::list<Point_2>&);
std::list<Segment> removeInnerLines(const std::list<Line>&);
std::list<Segment> getSegments(const std::list<Line>&);  // TODO: Remove this
bool doIntersect(const Segment&, const std::list<Segment>&, const Segment&);
Polygon_2 getPolygon(const std::list<Point_2>&);
bool onSegment(const Point_2&, const Point_2&, const Point_2&);
int orientation(const Point_2&, const Point_2&, const Point_2&);
bool do_intersect(const Segment&, const Segment&);
void fillDimensions(Tile&);
bool validateTile(const Tile&);
bool validatePolygon(const std::vector<Point_2>&);
double getMaxSide(const Tile&);
double getMaxAngle(const Tile&);
double getThirdSide(const Side&, const Side&, const double&);
double getTriangleArea(const double&, const double&, const double&);
double getTileArea(const Tile&);
double getOtherAngle(const Side&, const Side&, const double&, const char&);
double getMiddleAngle(const double&, const double&, const double&);
double getPolygonArea(const std::list<Line>&);
double getPolygonArea(const std::list<Segment>&);
double getPolygonArea(const std::list<Point_2>&);
std::list<Line> removeCommonLines(std::list<Line>);
std::list<Point_2> removeCommonPoints(std::list<Point_2>);
std::list<Line> removeLine(std::list<Line>, const Line&);
std::list<Point_2> removePoint(std::list<Point_2>, const Point_2&);
bool comparePoint(const Point_2&, const Point_2&);
std::list<Point_2> getSources(const std::list<Line>&);
std::list<Point_2> getSources(const std::list<Segment>&);
Point_2 getMidPoint(const Segment&);
Point_2 getCentroid(const std::list<Point_2>&);
bool comparePoints(const Point_2&, const Point_2&);
std::list<Point_2> sortClockwise(std::list<Point_2>);

#endif /* BOUNDARYDETECTION_HPP */
