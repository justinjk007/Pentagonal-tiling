#include <iostream>
#include "Tile.hpp"
#include "Side.hpp"
#include "CalculateGap.hpp"
#include "PrimitiveTile.hpp"

using namespace std;

double getGap(Tile tile)
{
  /*
   * This is the main method that calculated the gap between the tiles
   * when arranged.
   */
  if(!validateTile(tile))
    return 1.01;
  // throw 101;			// Tile not valid Exception

}

bool validateTile(Tile tile)
{
  /*
   * This method returns whether the Tile inputted is valid or not.
   * This method is used by getgap()
   */
  double max_side = getMaxSide(tile);
  if(tile.angle_e > 0)
    if(tile.side_ab.value+tile.side_bc.value+tile.side_cd.value+tile.side_de.value+tile.side_ea.value > (2*max_side))
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

double getMaxSide(Tile tile)
{
  /*
   * This method returns the biggest side of the tile.
   * Pretty bad way to do it I think
   * This method is used by ValidateTile
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
