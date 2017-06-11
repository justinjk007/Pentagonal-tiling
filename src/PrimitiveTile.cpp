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

void PrimitiveTile::del() {
  /**
   * Resets the contents of the primitiveTile.
   */
  this->size = 1;
}

void PrimitiveTile::drawPentagon() {
  Line current_line;
  Line next_line;
  double next_angle = 0;
  Point origin = {0,0};
  double length = this->pentagon.side[0].value;
  current_line = current_line.getLineWithRespectTo(origin,length);
  this->first_tile[0] = current_line;
  for (int i = 1; i < 5; i++) {
    next_angle = 180.0 - this->pentagon.angle[i];
    next_line =
      current_line.getLineWithRespectTo(next_angle, this->pentagon.side[i].value, i+1);
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

void PrimitiveTile::drawPrimitiveTile() {
  this->drawPentagon();
}
