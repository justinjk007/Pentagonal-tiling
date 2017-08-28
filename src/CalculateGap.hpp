/*
 * This is the main Header file that should be included in your
 * optimsation algorithm along with Tile.hpp as well
 */
#ifndef CALCULATEGAP_HPP
#define CALCULATEGAP_HPP
#include "PrimitiveTile.hpp"
#include "Side.hpp"
#include "Tile.hpp"
#include "concaveHull.hpp"

double getGap(Tile);
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
void printData(std::list<Line>);
void printData(std::list<Segment>);
void printData(std::list<Point_2>);
std::list<Line> removeCommonLines(std::list<Line>);
std::list<Line> removeLine(std::list<Line>, Line);
std::list<Point_2> addPoints(Line);
std::list<Point_2> getMorePoints(std::list<Line>);

#endif /* CALCULATEGAP_HPP */
