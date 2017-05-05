#include <iostream>
#include "Tile.h"
#include "CalculateGap.h"

using namespace std;

double CalculateGap(Tile tile){
  if(validateTile(tile))
    throw "TileInvalidException";
}

bool validateTile(Tile tile){
  if(tile.angle_a+tile.angle_b+tile.angle_c+tile.angle_d < 540)
    if(tile.side_a+tile.side_b+tile.side_c+tile.side_d < tile.side_e)
      return true;
    else
      return false;
  else
    return false;
}
