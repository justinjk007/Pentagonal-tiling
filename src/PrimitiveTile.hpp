/**
 * This structure defines a primitive tile, which is linkedlist of
 * connected tiles making use of the Link, Side and the Tile
 * strcuture.
 */
#ifndef PRIMITIVETILE_HPP
#define PRIMITIVETILE_HPP
#include "Side.hpp"
#include "Tile.hpp"

class PrimitiveTile{
public:
  Tile pentagon;
  Link* next;
  int size;
  bool checkSide(Side);
  void addTile(Tile tile);
  PrimitiveTile(Tile tile){
    this->pentagon = tile;
    this->link = NULL;
    this->size = 1;
  }
};

#endif /* PRIMITIVETILE_HPP */
