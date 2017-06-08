/**
 * This structure defines a primitive tile, which is linkedlist of
 * connected tiles making use of the Link, Side and the Tile
 * strcuture.
 */
#ifndef PRIMITIVETILE_HPP
#define PRIMITIVETILE_HPP
#include "Side.hpp"
#include "Tile.hpp"
#include "Square.hpp"
#include "myGeometry.hpp"
#include "Link.hpp"

class PrimitiveTile
{
public:
  Line first_tile[5];
  Tile pentagon;
  Link links[1000];  //Max size of the primitive tile for now = 1000.
  int size;
  int count;
  bool isLinkable(Link);
  void print();
  void drawPentagon(Tile);
  void drawPrimitiveTile(Tile,int,int);
  void del();
  PrimitiveTile(Tile tile)
      {
	this->count = 0;
	this->pentagon = tile;
	this->size = 1; // Because creating the primitive tile means there
	// should be at least one pentagon to start from
      }
};

#endif /* PRIMITIVETILE_HPP */
