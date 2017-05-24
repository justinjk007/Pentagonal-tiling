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
      if (tile.side[0].value + tile.side[1].value + tile.side[2].value +
          tile.side[3].value + tile.side[4].value >
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
  double max_side = tile.side[0].value;
  if (tile.side[1].value > max_side)
    max_side = tile.side[1].value;
  if (tile.side[2].value > max_side)
    max_side = tile.side[2].value;
  if (tile.side[3].value > max_side)
    max_side = tile.side[3].value;
  if (tile.side[4].value > max_side)
    max_side = tile.side[4].value;
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
  double ac = getThirdSide(tile.side[0], tile.side[1], tile.angle_b);
  double ce = getThirdSide(tile.side[2], tile.side[3], tile.angle_d);
  double triangle1 =
    getTriangleArea(tile.side[0].value, tile.side[1].value, ac);
  double triangle2 =
    getTriangleArea(tile.side[2].value, tile.side[3].value, ce);
  double triangle3 =
    getTriangleArea(ac, ce, tile.side[4].value);
  double pentagonArea = triangle1 + triangle2 + triangle3;
  return pentagonArea;
}
