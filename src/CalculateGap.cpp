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
    if(tile.side_ab+tile.side_bc+tile.side_cd+tile.side_de+tile.side_ea > (2*max_side))
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
  double max_side = tile.side_ab;
  if (tile.side_bc > max_side)
    max_side = tile.side_bc;
  if (tile.side_cd > max_side)
    max_side = tile.side_cd;
  if (tile.side_de > max_side)
    max_side = tile.side_de;
  if (tile.side_ea > max_side)
    max_side = tile.side_ea;
  return max_side;
}
