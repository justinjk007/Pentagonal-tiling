/*
 * This is the main Header file that should be included in your
 * optimsation algorithm along with Tile.hpp as well
 */
#ifndef CALCULATEGAP_HPP
#define CALCULATEGAP_HPP
#include "PrimitiveTile.hpp"
#include "pentagonlib_Export.h" // Include the linker header file for the dll
#include "Side.hpp"
#include "Tile.hpp"

typedef double dd; // Neat

pentagonlib_EXPORT double getFitness(dd, dd, dd, dd, dd, dd, dd, dd, dd);
double getGap(Tile);
double calculateGap(Tile, int, int);
bool validateTile(Tile);
double getMaxSide(Tile);
double getMaxAngle(Tile);
double getThirdSide(Side, Side, double);
double getTriangleArea(double, double, double);
double getTileArea(Tile);
double getOtherAngle(Side, Side, double, char);

#endif /* CALCULATEGAP_HPP */
