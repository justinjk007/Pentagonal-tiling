#include "PrimitiveTile.hpp"
#include <iostream>

using namespace std;

bool PrimitiveTile::checkSide(Side side){
  return false;
}

bool PrimitiveTile::addTile(Tile tile,Link link){
  if(!(link.from == link.to))
    return false;
  else{
    Tile new_tile;
    new_tile = tile;
    this->next = &new_tile;
    size++;
    links[size] = &link;
    return true;
  }
}

void PrimitiveTile::print(){
  cout << "\n";
  for (int i = 1; i <= this->size; i++)
    {
      cout << this->size << "\n";
      cout << this->links[i]->from <<"  "<<links[i]->to<<"\n";
    }

}
