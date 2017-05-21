#include "PrimitiveTile.hpp"
#include <iostream>

using namespace std;

bool PrimitiveTile::addTile(Link link) {
  if (!(link.from == link.to))
    return false;
  else {
    this->links[size] = link;
    this->size++;
    return true;
  }
}

void PrimitiveTile::print() {
  printf("\n");
  printf("%i\n", this->size);
  for (int i = 1; i < this->size; i++) {
    printf("%0.3f  %0.3f\n", this->links[i].from, this->links[i].to);
  }
}
