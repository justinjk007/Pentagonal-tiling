#include "PrimitiveTile.hpp"
#include <iostream>
#include <fstream>
#include <array>
#include <string>

using namespace std;

bool PrimitiveTile::isLinkable(Link link) {
  if (!(link.from.value == link.to.value))
    return false;
  else
  return true;
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
  Line current_line;
  Line next_line;
  double next_angle = 0;
  Point origin = {0,0};
  double length = tile.side[0].value;
  current_line = current_line.getLineWithRespectTo(origin,length);
  this->first_tile[0] = current_line;
  for (int i = 1; i < 5; i++) {
    next_angle = 180.0 - tile.angle[i];
    next_line =
      current_line.getLineWithRespectTo(next_angle, tile.side[i].value, i+1);
    this->first_tile[i] = next_line;
    current_line = next_line;
  }
  ofstream myfile;
  string file_name = "example";
  file_name += this->count;
  this->count++;
  file_name += ".csv";
  std::cout << file_name;
  myfile.open(file_name);
  myfile << "x,y,\n";
  for (int i = 0; i < 5; ++i) {
    myfile << this->first_tile[i].start.x_cord << "," << this->first_tile[i].start.y_cord
	   << "\n";
  }
  myfile << this->first_tile[0].start.x_cord << "," << this->first_tile[0].start.y_cord
         << "\n"; // So that it will complete a circle or a this->first_tile.
  myfile.close();
}

void PrimitiveTile::drawPrimitiveTile(Tile tile, int i, int j) {
  this->drawPentagon(tile);
}
