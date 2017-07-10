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
   * Resets the contents of the primitiveTile.
   */
  this->lines.clear(); // Delete the contents of the list
  this->size = 1;
}


void PrimitiveTile::drawPentagon(int from, int to) {
  /**
   * This was hard work okay, this draws the pentagon meaning they
   * give out the co-ordinates from the lengths and angles if a
   * pentagon. Parameters are the side conneted from and to of a new
   * pentagon.
   */
  Line first_line;
  Line current_line;
  Line diagonal; // The line that connects the 1st and the end of the 2nd line.
  Line next_line;
  double next_angle = 0;
  double diagonal_angle = 0;
  double diagonal_length = 0;
  Point origin = {0, 0};
  int moded_index = 0;
  int type1 = 0;
  int type2 = 0;
  int i =1; // Becuase we are already finding line 1 here
  if (!this->lines.empty()) {
    moded_index = to % 5; // This is done to rotate the first pentagon
    list<Line>::iterator it = this->lines.begin();
    advance(it, 2);
    current_line = *it;
    current_line = current_line.reverse();
    this->lines.push_back(current_line);
    first_line = current_line;
  } else {
    // ---------- Finding the first line here
    moded_index = (from + 3) % 5; // This is done to rotate the first pentagon
    current_line = current_line.getLineWithRespectTo(origin, this->pentagon.side[moded_index].value);
    this->lines.push_back(current_line);
    first_line = current_line;
    // ---------- Finding the first line here
  }
  moded_index = (moded_index + 1) % 5; // Wraparound like a circle array
  while (i < 5) {
    next_angle = this->pentagon.angle[moded_index];
    // TODO Check if +4 and -1 are the same on paper
    diagonal_length = getThirdSide(this->pentagon.side[(moded_index + 4) % 5], this->pentagon.side[moded_index],next_angle);
    diagonal_angle = getOtherAngle(this->pentagon.side[(moded_index + 4) % 5], this->pentagon.side[moded_index], next_angle, 'a');
    diagonal = current_line.getLineWithRespectTo(diagonal_angle, diagonal_length, type1,'d');
    next_line = current_line.getLineWithRespectTo(180-next_angle, this->pentagon.side[moded_index].value, type2, 's');
    double diff = diagonal.end.x_cord - next_line.end.x_cord;
    if (diff <= 0.1 && diff >= -0.1) {
      type1 = 0; // Reset types after every line
      type2 = 0; // Reset types after every line
      this->lines.push_back(next_line);
      current_line = next_line;
      ++i;
      moded_index = (moded_index + 1) % 5; // Wraparound like a circle array
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
  this->lines.pop_back(); // Remove the last added line
  current_line.end = first_line.start; // This what the origin and end are always the same points
  this->lines.push_back(current_line); // Add the modified line to the end
}

void PrimitiveTile::drawPentagonRev(int from, int to) {
  /**
   * This draw the pentagon in Reverse
   */
  Line first_line;
  Line current_line;
  Line diagonal; // The line that connects the 1st and the end of the 2nd line.
  Line next_line;
  double next_angle = 0;
  double diagonal_angle = 0;
  double diagonal_length = 0;
  Point origin = {0, 0};
  int moded_index = 0;
  int type1 = 0;
  int type2 = 0;
  int i =1; // Becuase we are already finding line 1 here
  if (!this->lines.empty()) {
    moded_index = to % 5; // This is done to rotate the first pentagon
    list<Line>::iterator it = this->lines.begin();
    advance(it, 2);
    current_line = *it;
    current_line = current_line.reverse();
    this->lines.push_back(current_line);
    first_line = current_line;
  } else {
    // ---------- Finding the first line here
    moded_index = (from + 3) % 5; // This is done to rotate the first pentagon
    current_line = current_line.getLineWithRespectTo(origin, this->pentagon.side[moded_index].value);
    std::cout << "\nModed index is " << moded_index << "\n";
    this->lines.push_back(current_line);
    first_line = current_line;
    // ---------- Finding the first line here
  }
  std::cout << "\nModed index is " <<moded_index<< "\n";
  moded_index = (moded_index + 1) % 5; // Wraparound like a circle array
  while (i < 5) {
    next_angle = this->pentagon.angle[moded_index];
    std::cout << "\nNext angle is " <<next_angle<< "\n";
    // TODO Check if +4 and -1 are the same on paper
    diagonal_length = getThirdSide(this->pentagon.side[(moded_index + 4) % 5], this->pentagon.side[moded_index],next_angle);
    diagonal_angle = getOtherAngle(this->pentagon.side[(moded_index + 4) % 5], this->pentagon.side[moded_index], next_angle, 'a');
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
      type1 = 0; // Reset types after every line
      type2 = 0; // Reset types after every line
      this->lines.push_back(next_line);
      current_line = next_line;
      ++i;
      moded_index = (moded_index + 1) % 5; // Wraparound like a circle array
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
  this->lines.pop_back(); // Remove the last added line
  current_line.end = first_line.start; // This what the origin and end are always the same points
  this->lines.push_back(current_line); // Add the modified line to the end
  cout << "Finished drawing a pentagon ------------------************************";
}

void PrimitiveTile::writeToFile() {
  /**
   * Write the lines list to file so it can be plotted for debugging
   * and viewing the creation
   */
  ofstream myfile;
  string file_name = "example.csv";
  myfile.open(file_name, std::ios_base::app);
  list<Line>::iterator it = this->lines.begin();
  list<Line>::iterator temp_it = it; // Temporary storage fo the main iterator
  int i = 0;
  Point i_need_this = this->lines.begin()->start;
  while (it != this->lines.end()) {
    myfile << it->start.x_cord << ","
           << it->start.y_cord << "\n";
    temp_it = it;
    ++it;
    i += 1;
    if (i % 5 == 0) {
      temp_it--;
      myfile << i_need_this.x_cord << "," << i_need_this.y_cord << "\n";
      advance(temp_it,2);
      if(temp_it != this->lines.end())
	i_need_this = temp_it->start;
    }
  }
  myfile.close();
}

void PrimitiveTile::writeToFileRaw() {
  /**
   * Write the lines list to file in raw, meaning the coordinates of
   * points of each line in the list, this is just for viewing and not
   * for plotting.
   */
  ofstream myfile;
  string file_name = "rawData.csv";
  myfile.open(file_name);
  myfile << "x,y,\n";
  list<Line>::iterator it = this->lines.begin();
  while (it != this->lines.end()) {
    myfile << it->start.x_cord << ","
           << it->start.y_cord << "\n";
    myfile << it->end.x_cord << ","
           << it->end.y_cord << "\n";
    ++it;
  }
  myfile.close();
}

Square PrimitiveTile::drawSquare(double area) {
  /**
   * [3](0,side) +----------+ [2](side,side)
   *             |          |
   *             |  Sqaure  |
   *             |          |
   *     [0](0,0)+----------+ [1](0,side)
   * The area passed is the area of the primitive tile.
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
  ofstream myfile;
  string file_name = "example.csv";
  myfile.open(file_name);
  myfile << "x,y,\n";
  myfile << square.point[0].x_cord << "," << square.point[0].y_cord << "\n";
  myfile << square.point[1].x_cord << "," << square.point[1].y_cord << "\n";
  myfile << square.point[2].x_cord << "," << square.point[2].y_cord << "\n";
  myfile << square.point[3].x_cord << "," << square.point[3].y_cord << "\n";
  myfile << square.point[0].x_cord << "," << square.point[0].y_cord << "\n"; // Complete circle
  myfile.close();
  this->this_square = square;
  return square;
}

void PrimitiveTile::doTiling(double t_x1, double t_y1, double t_x2, double t_y2) {
  /**
   * This method tile the primitiveTile with the given arguments. t_x1
   * is the translation in the x-axis and t_y1 in y-axis respectively
   * for tiling rightwards. t_x2 is the translation in the x-axis and
   * t_y2 in y-axis respectively for tiling upwards.
   */
  std::list<Line> original_p_tile = this->lines; // Stores the lines of the original primitivetile.
  std::list<Line> temp_p_tile; // Stores the original temporarily for translation.
  std::list<Line> last_p_tile; // Stores the lines last drawn primitivetile
  list<Line>::iterator it = this->lines.begin();

  // Get the translation rightwards
  it = this->lines.begin();
  double tpx1 = it->end.x_cord;
  double tpy1 = it->end.y_cord;
  advance(it, 3);
  double tpx2 = it->end.x_cord;
  double tpy2 = it->end.y_cord;
  t_x1 = tpx1 - tpx2;
  t_y1 = tpy1 - tpy2;
  // Get the translation rightwards

  // Get the translation upwards
  it = this->lines.begin();
  tpx1 = it->start.x_cord;
  tpy1 = it->start.y_cord;
  advance(it, 9);
  tpx2 = it->start.x_cord;
  tpy2 = it->start.y_cord;
  t_x2 = tpx2 - tpx1;
  t_y2 = tpy2 - tpy1;
  // Get the translation upwards

  temp_p_tile = original_p_tile;
  while (this->count <= 24) {
    /**
     * The loop is counted until tile count becomes 24 or when we
     * can't draw anymore tiles without begin completely outside the
     * sqaure(Which is checked by break statements).
     */
    // Reset this in the begining of iteratrion
    bool right_flag = true;
    bool transition_flag = true;
    bool done_flag = false;
    while (this->count <= 24 && this->count != 1) { // This loop handles the leftwards transition.
      temp_p_tile = translate(t_x1*(-1),t_y1*(-1),temp_p_tile); // Translate left
      last_p_tile = temp_p_tile;
      if(!checkIfFullyInsideForLeft(last_p_tile) || checkIfFullyOutsideForUp(last_p_tile)){
    	// Check if we can draw anymore inside the sqaure when transition left
    	break;
      }
      this->lines.splice(this->lines.end(), temp_p_tile); // Append main list with temp_list
      this->count++;
      // Splicing empties temp_p_tile so we re-assign it here.
      temp_p_tile = last_p_tile; // Inter-change last drawn tile for next translation.
    }
    temp_p_tile = original_p_tile;
    while (this->count <= 24 && right_flag) { // This loop handles the rightwards transition.
      temp_p_tile = translate(t_x1,t_y1,temp_p_tile); // Translate right
      last_p_tile = temp_p_tile;
      if(checkIfFullyOutsideForRight(last_p_tile)){
	// Check if we can draw anymore inside the sqaure when transition right
	done_flag = true;
	break;
      }
      this->lines.splice(this->lines.end(), temp_p_tile); // Append main list with temp_list
      this->count++;
      // Splicing empties temp_p_tile so we re-assign it here.
      temp_p_tile = last_p_tile; // Inter-change last drawn tile for next translation.
      right_flag = checkIfOutsideForRight(last_p_tile);
    }
    if(done_flag)
      break;
    temp_p_tile = original_p_tile;
    while (this->count <= 24 && transition_flag) { // This loop handles the upwards transition.
      temp_p_tile = translate(t_x2, t_y2, temp_p_tile); // Translate up
      last_p_tile = temp_p_tile;
      if (!checkIfFullyOutsideForUp(last_p_tile)) {
	original_p_tile = last_p_tile; // Replace original tile with this
	this->lines.splice(this->lines.end(), temp_p_tile); // Append main list with temp_list
	this->count++;
	temp_p_tile = last_p_tile;
	transition_flag = false; // Stop transition we have the correct upwards transition
      } else { // If the tile is fully outside
        printf("\n\n\nHERE\n\n\n");
        temp_p_tile = original_p_tile;
        temp_p_tile = translate(t_x1, t_y1, temp_p_tile); // Translate right again
        last_p_tile = temp_p_tile;
        original_p_tile = last_p_tile; // Replace original tile with this
      }
    }
    if (!(this->count <= 24))
      break;
  }

  printf("\nNumber of primitive tiles drawn is %d\n\n", this->count);
}

std::list<Line> PrimitiveTile::translate(double t_x, double t_y, std::list<Line> tile ) {
  list<Line>::iterator it;
  for (it = tile.begin(); it != tile.end(); ++it) {
    // Translation rightwards is applied here
    it->start.x_cord += t_x;
    it->start.y_cord += t_y;
    it->end.x_cord += t_x;
    it->end.y_cord += t_y;
  }
  return tile;
}

bool PrimitiveTile::checkIfOutsideForRight(std::list<Line> checkable) {
  /**
   * This method checks through all the points in the given list of
   * lines and return TRUE if none if none of the points lie outside
   * the square of the primtive tile and FALSE if any of the points
   * are outside the sqaure of the primitive tile.
   * "checkable" is the list to be checked.
   */
  for (list<Line>::iterator it = checkable.begin(); it != checkable.end(); ++it) {
    if(it->start.x_cord >= this->this_square.point[1].x_cord)
      return false;
    if (it->start.y_cord <= 0 )
      return false;
  }
  return true;
}

bool PrimitiveTile::checkIfOutsideForUp(std::list<Line> checkable) {
  /**
   * This method checks through all the points in the given list of
   * lines and return TRUE if none if none of the points lie outside
   * the square of the primtive tile and FALSE if any of the points
   * are outside the sqaure of the primitive tile.
   * "checkable" is the list to be checked.
   */
  for (list<Line>::iterator it = checkable.begin(); it != checkable.end(); ++it) {
    // if(it->start.x_cord >= this->this_square.point[1].x_cord)
    //   return false;
    if (it->start.y_cord <= 0 || it->start.y_cord >= this->this_square.point[2].y_cord)
      return false;
  }
  return true;
}

bool PrimitiveTile::checkIfFullyOutsideForUp(std::list<Line> checkable) {
  /**
   * This method checks through all the points in the given list of
   * lines and return TRUE if all the points are outside the sqaure.
   * "checkable" is the list to be checked.
   */
  bool value = true;
  for (list<Line>::iterator it = checkable.begin(); it != checkable.end(); ++it) {
    if (it->start.y_cord >= this->this_square.point[2].y_cord && value)
      ;
    else
      value = false;
  }
  return value;
}

bool PrimitiveTile::checkIfFullyOutsideForRight(std::list<Line> checkable) {
  /**
   * This method checks through all the points in the given list of
   * lines and return TRUE if all the points are outside the sqaure.
   * "checkable" is the list to be checked.
   */
  bool value = true;
  for (list<Line>::iterator it = checkable.begin(); it != checkable.end(); ++it) {
    if(it->start.x_cord >= this->this_square.point[1].x_cord)
      ;
    else
      value = false;
  }
  return value;
}

bool PrimitiveTile::checkIfFullyInsideForLeft(std::list<Line> checkable) {
  /**
   * This method checks through all the points in the given list of
   * lines and return TRUE if all the points are outside the sqaure.
   * "checkable" is the list to be checked.
   */
  bool value = true;
  for (list<Line>::iterator it = checkable.begin(); it != checkable.end(); ++it) {
    if(it->start.x_cord >= this->this_square.point[0].x_cord)
      ;
    else
      value = false;
  }
  return value;
}
