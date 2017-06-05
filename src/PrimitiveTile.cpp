#include "PrimitiveTile.hpp"
#include <iostream>
#include <fstream>

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
  double next_angle = 0;
  Point origin = {0,0};
  double length = tile.side[0].value;
  current_line = current_line.getLineWithRespectTo(origin,length);
  pentagon[0] = current_line;
  for (int i = 1; i < 5; ++i)
    {
      next_angle = 180.0 - tile.angle[i];
      next_line = current_line.getLineWithRespectTo(next_angle, tile.side[i].value);
      pentagon[i] = current_line;
      current_line = next_line;
    }
  ofstream myfile;
  myfile.open ("example.csv");
  myfile << "This is the first cell in the first column.\n";
  myfile << "a,b,c,\n";
  myfile << "c,s,v,\n";
  myfile << "1,2,3.456\n";
  myfile << "semi;colon";
  myfile.close();
}

void PrimitiveTile::drawPrimitiveTile() {

}
