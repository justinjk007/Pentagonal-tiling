/*
 * This is the main Header file that should be included in your
 * optimsation algorithm along with Tile.hpp as well
 */
#ifndef CALCULATEGAP_HPP
#define CALCULATEGAP_HPP
#include "PrimitiveTile.hpp"
#include "Side.hpp"
#include "Tile.hpp"
#include "boundaryDetection.hpp"
#include "myGeometry.hpp"

class CalculateGap
{
   public:
    double getGap(const Tile&);
    void getGap(double*, double*);
    double calculateGap(const Tile&, const int&, const int&);
};
#endif /* CALCULATEGAP_HPP */
