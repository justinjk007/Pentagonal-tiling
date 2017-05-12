#ifndef PRIMITIVETILE_HPP
#define PRIMITIVETILE_HPP
#include "Side.hpp"
#include "Tile.hpp"

class PrimitiveTile{
private:
  Tile tile_here ={3.22, 3.10, 2.20, 2.63, 3.43, 118, 39, 230, 66};
public:
  bool checkSide(Side);
};

#endif /* PRIMITIVETILE_HPP */
