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

typedef double dd;

double getGap(Tile);
double getGap(dd, dd, dd, dd, dd, dd, dd, dd, dd);
void getGap(double* , double*);
double calculateGap(Tile, int, int);
bool validateTile(Tile);
double getMaxSide(Tile);
double getMaxAngle(Tile);
double getThirdSide(Side, Side, double);
double getTriangleArea(double, double, double);
double getTileArea(Tile);
double getOtherAngle(Side, Side, double, char);
double getPolygonArea(std::list<Line>);
double getPolygonArea(std::list<Segment>);
double getPolygonArea(std::list<Point_2>);
void printData(std::list<Line>);
void printData(std::list<Segment>);
void printData(std::list<Point_2>);
std::list<Line> removeCommonLines(std::list<Line>);
std::list<Point_2> removeCommonPoints(std::list<Point_2>);
std::list<Line> removeLine(std::list<Line>, Line);
std::list<Point_2> removePoint(std::list<Point_2>, Point_2);
bool comparePoint(Point_2, Point_2);
std::list<Point_2> getSources(std::list<Line>);
std::list<Point_2> getSources(std::list<Segment>);
Point_2 getMidPoint(Segment);
Point_2 getCentroid(std::list<Point_2>);
bool comparePoints(Point_2, Point_2);
std::list<Point_2> sortClockwise(std::list<Point_2>);

#endif /* CALCULATEGAP_HPP */
