/**
 * This structure defines a primitive tile, which is linkedlist of
 * connected tiles making use of the Link, Side and the Tile
 * strcuture.
 */
#ifndef PRIMITIVETILE_HPP
#define PRIMITIVETILE_HPP
#include "Link.hpp"
#include "Side.hpp"
#include "Tile.hpp"

class PrimitiveTile {
public:
  Tile pentagon;
  Tile *next;
  Link *links[1000] = {NULL}; // Max size of the primitive tile for now = 1000.
  int size;
  bool checkSide(Side);
  bool addTile(Tile tile, Link link);
  void print();
  PrimitiveTile(Tile tile) {
    this->pentagon = tile;
    this->next = NULL;
    this->size = 1;
  }
};

#endif /* PRIMITIVETILE_HPP */
