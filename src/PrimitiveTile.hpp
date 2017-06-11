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
  int connector_sides[1000]; // Max size of the connectors for now = 1000.
  int size; // This accounts for the number of tiles in the primitive tile.
  bool isLinkable(Link);
  void drawPentagon();
  void drawPrimitiveTile();
  void addTile(double, double);
  void del();
  Square drawSquare(double area);
  PrimitiveTile(Tile tile) {
    std::fill_n(this->connector_sides, 1000, 0);
    this->pentagon = tile;
    this->size = 1; // Obviously we need atleast one tile.
  }
};

#endif /* PRIMITIVETILE_HPP */
