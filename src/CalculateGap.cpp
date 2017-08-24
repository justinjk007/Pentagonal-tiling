#include "CalculateGap.hpp"
#include "PrimitiveTile.hpp"
#include "myGeometry.hpp"
#include <math.h>
#include <stdlib.h>
#include <iostream>

#define PI 3.14159265
using namespace std;

double getGap(Tile tile) {
  /*
   * This is the main method that returns the gap minimum between the
   * tiles when arranged with any particular order. Current this only
   * calculates gap between primitive tiles of size 2. This returns
   * the minimum gap from the list of combinateions.
   */
  if (!validateTile(tile)) {
    exit(1);
    printf("\nThe tile inputted was invalid");
  }

  int gap_index = 0;
  double gap_list[25];
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      gap_list[gap_index] = calculateGap(tile, i, j);
      gap_index++;
    }
  }

  // Returning the minimumgap in the gap list
  double min_gap = gap_list[0];
  int gap_list_size = (sizeof gap_list) / (sizeof gap_list[0]);
  for (int i = 0; i < gap_list_size; ++i) {
    if (gap_list[i] >= 0 && gap_list[i] < min_gap)
      min_gap = gap_list[i];
  }
  return min_gap;
}

double calculateGap(Tile tile, int i, int j) {
  double tile_area = getTileArea(tile);
  double p_area = 2 * tile_area; // This is the area of the primitiveTile
  PrimitiveTile newSample(tile);
  newSample.drawSquare(p_area);
  newSample.drawPentagon(i,j); // Draw the first pentagon
  Link link(tile.side[i], tile.side[j]);
  if (newSample.isLinkable(link)) {
    newSample.drawPentagon(i,j);
    newSample.doTiling(0, 0, 0, 0); // For now TODO Remove this
    // printf("\nNumber of primitive tiles drawn is %d\n", newSample.count);
    double gap = ((25 - newSample.count) * p_area);
    // printf("The gap for the inputted tile is: %f", gap);
    newSample.writeToFileRaw();
    newSample.writeToFile();
    return gap;
  }
  else
    return -101;
}

bool validateTile(Tile tile) {
  /*
   * This method returns whether the Tile inputted is valid or not.
   * This method is used by getgap()
   */
  double max_side = getMaxSide(tile);
  double max_angle = getMaxAngle(tile);
  if (max_angle <= 180.00)
    if (tile.angle[4] > 0)
      if (tile.side[0].value + tile.side[1].value + tile.side[2].value +
	  tile.side[3].value + tile.side[4].value >
          (2 * max_side))
        // 2 x Biggest side becauase we don't know which one is the
        // biggest side now and we should count that twice on the right
        // side because we are taking the sum of all sides instead of
        // the other 4..soo..
        return true;
      else
        return false;
    else
      return false;
  else
    return false;
}

double getMaxSide(Tile tile) {
  /*
   * This method returns the biggest side of the tile.
   */
  double max_side = tile.side[0].value;
  for (int i = 0; i < 5; ++i) {
    if (tile.side[i].value > max_side)
      max_side = tile.side[i].value;
  }
  return max_side;
}

double getMaxAngle(Tile tile) {
  /*
   * This method returns the biggest angle of the tile.
   */
  double max_angle = tile.angle[0];
  for (int i = 0; i < 5; ++i) {
    if (tile.angle[i] > max_angle)
      max_angle = tile.angle[i];
  }
  return max_angle;
}

double getThirdSide(Side a, Side b, double angle) {
  /*
   * This method returns the third side of the triangle formed inside
   * a polygon used for area calculating purposes. Angle should be
   * passed in degrees
   */
  angle = angle * PI / 180.0;
  double side_c = sqrt((a.value * a.value) + (b.value * b.value) -
                       (2 * a.value * b.value * cos(angle)));
  return side_c;
}

double getOtherAngle(Side a, Side b, double angle_b, char which_angle) {
  /**
   * This method uses sine law to find the angle b/w a and c or b and
   * c .Here the angle passed is the angle b/w the sides a and b. The
   * character passed is the angle to be found which can be a or c
   * because the angle we know that's in the middle is b.Angle should
   * be passed in degrees
   */
  double other_angle = 0.0;
  double part_one;
  double side_c_length = getThirdSide(a,b,angle_b);
  if (which_angle == 'a') {
    part_one = (sin(angle_b * PI / 180.0) * b.value) / side_c_length;
    other_angle = asin(part_one) * 180.0 / PI;
    return other_angle;
  } else if (which_angle == 'c') {
    part_one = (sin(angle_b * PI / 180.0) * a.value) / side_c_length;
    other_angle = asin(part_one) * 180.0 / PI;
    return other_angle;
  } else
    return other_angle;
}

double getTriangleArea(double a, double b, double c) {
  /*
   * This method returns the Area of the triagle using Heron's
   * Formulae
   */
  double S = (a + b + c) / 2;
  double area = sqrt(S * (S - a) * (S - b) * (S - c));
  return area;
}

double getTileArea(Tile tile) {
  /*
   * This method returns the Area of the pentagon dividing it into
   * three triangles, calculating its area and summing them up.
   */
  double ac = getThirdSide(tile.side[0], tile.side[1], tile.angle[1]);
  double ce = getThirdSide(tile.side[2], tile.side[3], tile.angle[3]);
  double triangle1 =
    getTriangleArea(tile.side[0].value, tile.side[1].value, ac);
  double triangle2 =
    getTriangleArea(tile.side[2].value, tile.side[3].value, ce);
  double triangle3 = getTriangleArea(ac, ce, tile.side[4].value);
  double pentagonArea = triangle1 + triangle2 + triangle3;
  return pentagonArea;
}

double getPolygonArea(std::list<Line> polygon) {
  /**
   * This method implements calculating the area of a polygon using
   * the shoelace formula. The list the passed should contain the
   * lines that create the polygon/polygons.
   */
  double sum = 0, diff = 0, area = 0;
  double x1, y1, x2, y2;
  // cout << "Begin ---\n";

  for (list<Line>::iterator it = polygon.begin(); it != polygon.end(); it++) {
      x1 = it->start.x;
      y1 = it->start.y;
      x2 = it->end.x;
      y2 = it->end.y;
      // printf("(%f x %f)  ---   (%f x %f)\n",x1,y2,y1,x2);
      sum += x1 * y2;
      diff += y1 * x2;
  }

  area = (1.0/2.0) * abs((sum - diff));
  return area;
}

double getPolygonArea(std::list<Point> polygon) {
  /**
   * This method implements calculating the area of a polygon using
   * the shoelace formula. The list the passed should contain the
   * points that create the polygon/polygons.
   */
  double sum = 0, diff = 0, area = 0;
  double x1, y1, x2, y2;
  // cout << "Begin ---\n";

  for (list<Point>::iterator it = polygon.begin(); it != polygon.end();) {
    bool flag = false;
    x1 = it->x;
    y1 = it->y;
    it++;
    if (it == polygon.end()) {
      it = polygon.begin();
      flag = true;
    }
    x2 = it->x;
    y2 = it->y;
    // printf("(%f x %f)  ---   (%f x %f)\n",x1,y2,y1,x2);
    sum += x1 * y2;
    diff += y1 * x2;
    if (flag) break;
  }

  area = (1.0/2.0) * abs((sum - diff));
  return area;
}

std::list<Line> removeCommonLines(std::list<Line> lines) {
  /**
   * This method is used remove duplicate Lines from the given Line
   * list, this will only work for the specific case I have. If a duplicate
   * is found both the original and the duplicate are removed from the
   * list. This is done to eliminate inner Line-segments of the
   * translated structure.
   */
  std::list<Line> new_lines = lines;

  while (!lines.empty()) {
    Line line1 = lines.front(); // Get the 1st line from the list
    lines.pop_front();          // Remove the same line from the list
    for (list<Line>::iterator it = lines.begin(); it != lines.end(); ++it)
      if (compareLine(line1, *it)) // Compare to see if same Lines exists
        new_lines = removeLine(new_lines, line1);
  }

  return new_lines;
}

std::list<Line> removeLine(std::list<Line> lines, Line val) {
  /**
   * Override function for list::remove rewritten for list<Line>
   */
  for (list<Line>::iterator it = lines.begin(); it != lines.end();) {
    if (compareLine(val, *it)) // If same lines exists
      it = lines.erase(it);
    else
      ++it;
  }
  return lines;
}
