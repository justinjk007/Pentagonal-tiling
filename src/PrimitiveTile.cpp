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
  // (5.09,5.80), (1.68,4.90), (1.48,1.38), (4.76,0.10), (7.00,2.83)
  myfile.open ("example.csv");
  myfile << "x,y,\n";
  for (int i = 0; i < 5; ++i)
    myfile <<pentagon[i].start.x_cord<<","<<pentagon[i].start.y_cord<< "\n";

  myfile <<pentagon[4].end.x_cord<<","<<pentagon[4].end.y_cord<< "\n"; // So that it will complete a circle
  myfile.close();
}

void PrimitiveTile::drawPrimitiveTile() {

}
