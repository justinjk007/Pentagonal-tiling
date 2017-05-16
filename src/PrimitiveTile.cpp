#include "PrimitiveTile.hpp"
#include <iostream>

using namespace std;

bool PrimitiveTile::addTile(Tile tile, Link link) {
  if (!(link.from == link.to))
    return false;
  else {
    Tile new_tile;
    new_tile = tile;
    this->next = &new_tile;
    this->links[size] = &link;
    this->size++;
    return true;
  }
}

void PrimitiveTile::print() {
  cout << "\n";
  cout << this->size<<"\n";
  for (int i = 1; i < this->size; i++) {
    cout << (int)this->links[i]->from << "  " << (int)links[i]->to << "\n";
  }
}
