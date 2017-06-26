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
#include <list>

class PrimitiveTile {
public:
  std::list<Line> lines; // Stores the lines of the boundaries primitive tile
  std::list<int> connector_sides; // Stores the indexes of the sides connected.
  Tile pentagon; // Stores the measurements of the tile or pentagon used.
  int size; // This accounts for the number of tiles in the primitive tile.
  int count; // Stores the number of primitivetile used in tiling
  bool isLinkable(Link);
  void drawPentagon(int, int);
  void addTile(int, int);
  void del();
  void writeToFile();
  void writeToFileRaw();
  Square drawSquare(double area);
  void doTiling(double,double,double,double);
  PrimitiveTile(Tile tile) {
    this->pentagon = tile;
    this->size = 1; // Obviously we need atleast one tile.
    this->count = 1;// Obviously we need atleast one primitive tile.
  }
};

#endif /* PRIMITIVETILE_HPP */
