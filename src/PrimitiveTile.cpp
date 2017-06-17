#include "PrimitiveTile.hpp"
#include "CalculateGap.hpp"
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
  this->connector_sides.push_back(from);
  this->connector_sides.push_back(to);
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
  Line diagonal; // The line that connects the 1st and the end of the 2nd line.
  Line next_line;
  double next_angle = 0;
  double diagonal_angle = 0;
  double diagonal_length = 0;
  Point origin = {0, 0};
  int correct_index = wrapAround(from);
  int moded_index = correct_index % 5;
  int type1 = 0;
  int type2 = 0;
  int i =1;
  current_line = current_line.getLineWithRespectTo(origin, this->pentagon.side[moded_index].value);
  std::cout << "\nModed index is " <<moded_index<< "\n";
  this->boundary.push_back(current_line);
  correct_index += 1;
  moded_index = correct_index % 5; // Wraparound like a circle array
  while(i < 5){ // TODO change 2 to 5, 2 was just for debugging.
    next_angle = this->pentagon.angle[moded_index];
    std::cout << "\nNext angle is " <<next_angle<< "\n";
    diagonal_length = getThirdSide(this->pentagon.side[(moded_index + 4) % 5], this->pentagon.side[moded_index],next_angle);
    diagonal_angle =getOtherAngle(this->pentagon.side[(moded_index + 4) % 5], this->pentagon.side[moded_index], next_angle, 'a');
    std::cout <<"This contraption is "<< (moded_index + 4) % 5 <<endl;
    std::cout << "\nFor the diagonal -------------" << "\n";
    std::cout << "Diagonal angle is " <<diagonal_angle<< "\n";
    diagonal = current_line.getLineWithRespectTo(diagonal_angle, diagonal_length, type1,'d');
    std::cout << "\nFor the line     -------------" << "\n";
    next_line = current_line.getLineWithRespectTo(180-next_angle, this->pentagon.side[moded_index].value, type2, 's');
    double diff = diagonal.end.x_cord - next_line.end.x_cord;
    std::cout << "Diff between the co-ordinates: " <<diff<< "\n";
    if (diff <= 0.1 && diff >= -0.1) {
      std::cout << "One side found***************" <<endl;
      type1 = 0;
      type2 = 0;
      this->boundary.push_back(next_line);
      current_line = next_line;
      ++i;
      correct_index += 1;
      moded_index = correct_index % 5; // Wraparound like a circle array
    } else {
      if (type1 == 0 && type2 == 0) {
        type1 = 1;
        continue;
      } else if (type1 == 1 && type2 == 0) {
        type2 = 1;
        continue;
      } else if (type1 == 1 && type2 == 1) {
        type1 = 0;
        continue;
      } else
	{
	  std::cout << "*******************************************************************************\n";
	  std::cout << "All options for finding co-ordinates covered program exited with exit status 1\n";
	  std::cout << "*******************************************************************************\n";
	  break;
	}
    }
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
  list<int>::iterator boundary_it = this->connector_sides.begin();
  this->drawFirstPentagon(this->connector_sides.front()); // Get the first element in the list
}

Square PrimitiveTile::drawSquare(double area) {
  /**
   * [3](0,side) +----------+ [2](side,side)
   *             |          |
   *             |  Sqaure  |
   *             |          |
   *     [0](0,0)+----------+ [1](0,side)
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
