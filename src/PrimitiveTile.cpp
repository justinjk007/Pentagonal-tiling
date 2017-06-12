#include "PrimitiveTile.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool PrimitiveTile::isLinkable(Link link) {
  /**
   * Check if the sides are linkable
   */
    if (!(link.from.value == link.to.value))
    return false;
  else
    return true;
}

void PrimitiveTile::addTile(int from, int to) {
  /**
   * Add a tile to the primitive tile after saving the combination of
   * the side used to connect it.
   */
  this->connector_sides[this->connector_num] = from;
  this->connector_sides[this->connector_num + 1] = to;
  this->connector_num += 2;
  this->size += 1;
}

void PrimitiveTile::del() {
  /**
   * Resets the size of the primitiveTile.
   */
  this->size = 1;
}

void PrimitiveTile::drawPentagon() {
  ;
}

void PrimitiveTile::drawFirstPentagon(int from) {
  Line current_line;
  Line next_line;
  double next_angle = 0;
  Point origin = {0, 0};
  int correct_index = wrapAround(from);
  int moded_index = 0;
  current_line = current_line.getLineWithRespectTo(origin, this->pentagon.side[correct_index].value);
  this->boundary.push_back(current_line);
  for (int i = 1; i < 5; i++) {
    correct_index += i;
    moded_index = correct_index % 5; // Wraparound like a circle array
    next_angle = 180.0 - this->pentagon.angle[moded_index];
    next_line = current_line.getLineWithRespectTo(next_angle, this->pentagon.side[moded_index].value, i + 1);
    this->boundary.push_back(next_line);
    current_line = next_line;
  }
  this->writeToFile();
}

void PrimitiveTile::writeToFile() {
  /**
   * Write the first pentagon to file, so it can be plotted
   */
  ofstream myfile;
  string file_name = "example.csv";
  myfile.open(file_name);
  myfile << "x,y,\n";
  for (list<Line>::iterator it = this->boundary.begin(); it != this->boundary.end(); ++it) {
    myfile << it->start.x_cord << ","
	   << it->start.y_cord << "\n";
  }
  myfile << this->boundary.begin()->start.x_cord << ","
	 << this->boundary.begin()->start.y_cord
	 << "\n"; // So that it will complete a circle or a this->boundary.
  myfile.close();
}

void PrimitiveTile::drawPrimitiveTile() {
  this->drawFirstPentagon(this->connector_sides[0]);
}

Square PrimitiveTile::drawSquare(double area) {
  /**
   * () +-------+ ()
   *    |       |
   *    |       |
   * () +-------+ ()
   */
  Square square;
  area = area * 25; // Make the area of the sqaure 25 times the primtive tile
  square.side = sqrt(area); // Get the side length of the square.
  square.point[0].x_cord = 0;
  square.point[0].y_cord = 0;
  square.point[1].x_cord = square.side;
  square.point[1].y_cord = 0;
  square.point[2].x_cord = square.side;
  square.point[2].y_cord = square.side;
  square.point[3].x_cord = 0;
  square.point[3].y_cord = square.side;
  return square;
}
