/*
 * This is the main Header file that should be included in your
 * optimsation algorithm along with Tile.hpp as well
 */
#ifndef CALCULATEGAP_HPP
#define CALCULATEGAP_HPP
#include "Tile.hpp"
#include "Side.hpp"

double getGap(Tile);
bool validateTile(Tile);
double getMaxSide(Tile);
double getMaxAngle(Tile);
double getThirdSide(Side, Side, double);
double getTriangleArea(Side, Side, Side);
double getPentagonArea(Tile);

#endif /* CALCULATEGAP_HPP */
