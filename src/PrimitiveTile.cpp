#include "PrimitiveTile.hpp"

bool PrimitiveTile::checkSide(Side side){
  return false;
}

bool PrimitiveTile::addTile(Tile tile,Link link){
  if(!(link.from->value == link.to->value))
    return false;
  else{
    Tile new_tile;
    new_tile = tile;
    this->next = &new_tile;
    links[size] = &link;
    size++;
    return true;
  }
}
