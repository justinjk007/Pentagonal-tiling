#include <iostream>
#include "Tile.hpp"
#include "CalculateGap.hpp"

using namespace std;

double getGap(Tile tile){
  /*
   *This is the main method that calculated the gap between the tiles when arranged.
   */
  if(!validateTile(tile))
    ;
  // throw 101;			// Tile not valid Exception
  return 7.7777;
}

bool validateTile(Tile tile){
  /*
   *This method returns whether the Tile inputted is valid or not.
   */
  if(tile.angle_a+tile.angle_b+tile.angle_c+tile.angle_d < 540)
    if(tile.side_a+tile.side_b+tile.side_c+tile.side_d < tile.side_e)
      return true;
    else
      return false;
  else
    return false;
}
