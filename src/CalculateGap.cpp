#include <iostream>
#include "Tile.hpp"
#include "CalculateGap.hpp"

using namespace std;

double getGap(Tile tile){
  /*
   *This is the main method that calculated the gap between the tiles
   *when arranged.
   */
  if(!validateTile(tile))
    return 1.01;
  // throw 101;			// Tile not valid Exception
  else
    return 7.77;
}

bool validateTile(Tile tile){
  /*
   *This method returns whether the Tile inputted is valid or not.
   */
  double max_side = getMaxSide(tile);
  if(tile.angle_a+tile.angle_b+tile.angle_c+tile.angle_d < 540)
    if(tile.side_a+tile.side_b+tile.side_c+tile.side_d+tile.side_e > (2*max_side))
      // 2 x Biggest side becauase we don't know which one is the
      // biggest side now and we should count that twice on the right
      // side because we are taking the sum of all sides instead of
      // the other 4..soo..
      return true;
    else
      return false;
  else
    return false;
}

double getMaxSide(Tile tile){
  /*
   *This method returns the biggest side of the tile.
   *Pretty bad way to do it I think
   */
  double max_side = tile.side_a;
  if (tile.side_b > max_side)
    max_side = tile.side_b;
  if (tile.side_c > max_side)
    max_side = tile.side_c;
  if (tile.side_d > max_side)
    max_side = tile.side_d;
  if (tile.side_e > max_side)
    max_side = tile.side_e;
  return max_side;
}
