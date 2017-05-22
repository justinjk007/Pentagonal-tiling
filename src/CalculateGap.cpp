#include "CalculateGap.hpp"
#include "PrimitiveTile.hpp"
#include <math.h>

#define PI 3.14159265
using namespace std;

double getGap(Tile tile) {
  /*
   * This is the main method that calculated the gap between the tiles
   * when arranged.
   */
  if (!validateTile(tile))
    return -101;		// Negative gap means the tile is not valid.
}

bool validateTile(Tile tile) {
  /*
   * This method returns whether the Tile inputted is valid or not.
   * This method is used by getgap()
   */
  double max_side = getMaxSide(tile);
  double max_angle = getMaxAngle(tile);
  if (max_angle <= 180.00)
    if (tile.angle_e > 0)
      if (tile.side_ab.value + tile.side_bc.value + tile.side_cd.value +
          tile.side_de.value + tile.side_ea.value >
          (2 * max_side))
        // 2 x Biggest side becauase we don't know which one is the
        // biggest side now and we should count that twice on the right
        // side because we are taking the sum of all sides instead of
        // the other 4..soo..
        return true;
      else
        return false;
    else
      return false;
  else
    return false;
}

double getMaxSide(Tile tile) {
  /*
   * This method returns the biggest side of the tile.
   */
  double max_side = tile.side_ab.value;
  if (tile.side_bc.value > max_side)
    max_side = tile.side_bc.value;
  if (tile.side_cd.value > max_side)
    max_side = tile.side_cd.value;
  if (tile.side_de.value > max_side)
    max_side = tile.side_de.value;
  if (tile.side_ea.value > max_side)
    max_side = tile.side_ea.value;
  return max_side;
}

double getMaxAngle(Tile tile) {
  /*
   * This method returns the biggest angle of the tile.
   */
  double max_angle = tile.angle_a;
  if (tile.angle_b > max_angle)
    max_angle = tile.angle_b;
  if (tile.angle_c > max_angle)
    max_angle = tile.angle_c ;
  if (tile.angle_d  > max_angle)
    max_angle = tile.angle_d ;
  if (tile.angle_e  > max_angle)
    max_angle = tile.angle_e ;
  return max_angle;
}

double getThirdSide(Side a, Side b, double angle) {
  /*
   * This method returns the third side of the triangle formed inside
   * a polygon used for area calculating purposes
   */
  angle = angle * PI / 180;
  double side_c = sqrt((a.value * a.value) + (b.value * b.value) -
                       (2 * a.value * b.value * cos(angle)));
  return side_c;
}

double getTriangleArea(double a, double b, double c) {
  /*
   * This method returns the Area of the triagle using Heron's
   * Formulae
   */
  double S = (a + b + c) / 2;
  double area = sqrt(S * (S - a) * (S - b) * (S - c));
  return area;
}

double getTileArea(Tile tile) {
  /*
   * This method returns the Area of the pentagon dividing it into
   * three triangles, calculating its area and summing them up.
   */
  double ac = getThirdSide(tile.side_ab, tile.side_bc, tile.angle_b);
  double ce = getThirdSide(tile.side_cd, tile.side_de, tile.angle_d);
  double triangle1 =
  getTriangleArea(tile.side_ab.value, tile.side_bc.value, ac);
  double triangle2 =
    getTriangleArea(tile.side_cd.value, tile.side_de.value, ce);
  double triangle3 =
    getTriangleArea(ac, ce, tile.side_ea.value);
  double pentagonArea = triangle1 + triangle2 + triangle3;
  return pentagonArea;
}
