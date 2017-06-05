#include "PrimitiveTile.hpp"
#include <iostream>

using namespace std;

bool PrimitiveTile::addTile(Link link) {
  if (!(link.from.value == link.to.value))
    return false;
  else {
    this->links[size] = link;
    this->size++;
    return true;
  }
}

void PrimitiveTile::print() {
  printf("\n");
  printf("Size of the primitive-tile is %i\n", this->size);
  for (int i = 1; i < this->size; i++) {
    printf("%0.3f  %0.3f\n", this->links[i].from.value,
           this->links[i].to.value);
  }
  printf("\n");
}


void PrimitiveTile::del() {
  /**
   * Resets the contents of the primitiveTile.
   */
  this->size = 1;
}

void PrimitiveTile::drawPentagon(Tile tile) {
  Line pentagon[5];
  Line current_line;
  Line next_line;
  Point origin = {0,0};
  double length = tile.side[0].value;
  current_line = current_line.getLineWithRespectTo(origin,length);
  pentagon[0] = current_line;
  for (int i = 0; i < 4; ++i)
    {
      next_line = current_line.getLineWithRespectTo(double, double);
    }
}

void PrimitiveTile::drawPrimitiveTile() {

}
