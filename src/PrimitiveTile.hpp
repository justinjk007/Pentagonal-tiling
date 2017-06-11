/**
 * This structure defines a primitive tile, which is linkedlist of
 * connected tiles making use of the Link, Side and the Tile
 * strcuture.
 */
#ifndef PRIMITIVETILE_HPP
#define PRIMITIVETILE_HPP
#include "Link.hpp"
#include "Side.hpp"
#include "Square.hpp"
#include "Tile.hpp"
#include "myGeometry.hpp"
#include <algorithm>

class PrimitiveTile {
public:
  Line first_tile[5]; // Stores the co-ordinates for the first pentagon drawn.
  Tile pentagon;      // Stores the measurements of the tile or pentagon used.
  int connector_sides[1000]; // Max size of the primitive tile for now = 1000.
  int size; // This accounts for the number of tiles in the primitive tile.
  int count;
  bool isLinkable(Link);
  void drawPentagon();
  void drawPrimitiveTile();
  void del();
  PrimitiveTile(Tile tile) {
    std::fill_n(this->connector_sides, 1000, 0);
    this->count = 0;
    this->pentagon = tile;
    this->size = 1; // Because creating the primitive tile means there
    // should be at least one pentagon to start from
  }
};

#endif /* PRIMITIVETILE_HPP */
