/*
 * This is the main Header file that should be included in your
 * optimsation algorithm along with Tile.hpp as well
 */
#ifndef CALCULATEGAP_HPP
#define CALCULATEGAP_HPP
#include "PrimitiveTile.hpp"
#include "Side.hpp"
#include "Tile.hpp"

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
double getPolygonArea(std::list<Point>);
std::list<Line> removeCommonLines(std::list<Line>);
std::list<Line> removeLine(std::list<Line>, Line);

#endif /* CALCULATEGAP_HPP */
