/*
 * This is the main Header file that should be included in your
 * optimsation algorithm along with Tile.hpp as well
 */
#ifndef CALCULATEGAP_HPP
#define CALCULATEGAP_HPP
#include <algorithm>
#include <list>
#include "PrimitiveTile.hpp"
#include "Side.hpp"
#include "Tile.hpp"
#include "boundaryDetection.hpp"

static Point_2 centroid;

double getGap(const Tile&);
void getGap(double*, double*);
double calculateGap(const Tile&, const int&, const int&);
bool validateTile(const Tile&);
double getMaxSide(const Tile&);
double getMaxAngle(const Tile&);
double getThirdSide(const Side&, const Side&, const double&);
double getTriangleArea(const double&, const double&, const double&);
double getTileArea(const Tile&);
double getOtherAngle(const Side&, const Side&, const double&, const char&);
double getPolygonArea(const std::list<Line>&);
double getPolygonArea(const std::list<Segment>&);
double getPolygonArea(const std::list<Point_2>&);
void printData(const std::list<Line>&);
void printData(const std::list<Segment>&);
void printData(const std::list<Point_2>&);
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
template<typename T>
void examineVector(const std::vector<T>&);

#endif /* CALCULATEGAP_HPP */
