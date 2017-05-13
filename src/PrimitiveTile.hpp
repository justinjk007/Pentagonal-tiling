/**
 * This structure defines a primitive tile, which is linkedlist of
 * connected tiles making use of the Link, Side and the Tile
 * strcuture.
 *
 */
#ifndef PRIMITIVETILE_HPP
#define PRIMITIVETILE_HPP
#include "Side.hpp"
#include "Tile.hpp"

class PrimitiveTile{
private:
  Tile pentagon;
  Tile* next_link;
  int size;
public:
  bool checkSide(Side);
  void addTile(Tile tile);
  PrimitiveTile(Tile tile){
    this->pentagon = tile;
    this->next_link = NULL;
    this->size = 1;
  }
};

#endif /* PRIMITIVETILE_HPP */
