#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GapTest
#include "CalculateGap.hpp"
#include "PrimitiveTile.hpp"
#include "Side.hpp"
#include "Tile.hpp"
#include "myGeometry.hpp"
#include "boundaryDetection.hpp"
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;

using namespace std;

BOOST_AUTO_TEST_CASE(validate) { // #1
  Tile tile = {5, 10, 5, 4.3197516, 5, 150, 60, 135, 90};
  BOOST_CHECK_EQUAL(validateTile(tile), true);
}

BOOST_AUTO_TEST_CASE(validate2) { // Complex pentagon #2
  Tile tile = {3.22, 3.10, 2.20, 2.63, 3.43, 118, 39, 330, 66};
  BOOST_CHECK_EQUAL(validateTile(tile), false);
}

BOOST_AUTO_TEST_CASE(validate3) { // #3
  Tile tile = {21, 24, 434, 54, 4, 40, 120, 130, 60};
  BOOST_CHECK_EQUAL(validateTile(tile), false);
}

BOOST_AUTO_TEST_CASE(max_side_test) { // #4
  Tile tile = {21, 24, 434, 54, 4, 40, 120, 120, 60};
  BOOST_CHECK_EQUAL(getMaxSide(tile), 434);
}

BOOST_AUTO_TEST_CASE(max_angle_test) { // #5
  Tile tile = {21, 24, 434, 54, 4, 40, 120, 130, 60};
  BOOST_CHECK_EQUAL(getMaxAngle(tile), 190);
}

BOOST_AUTO_TEST_CASE(AngleE) { // #6
  Tile tile = {21, 24, 434, 54, 4, 40, 120, 120, 60};
  BOOST_CHECK_EQUAL(tile.angle[4], 200);
}

BOOST_AUTO_TEST_CASE(tile_values_test) { // #7
  Tile tile = {10, 7, 21, 20, 30, 54, 54, 45, 45};
  BOOST_CHECK_EQUAL(tile.side[0].value, 10);
  BOOST_CHECK_EQUAL(tile.side[0].next->value, 7);
  BOOST_CHECK_EQUAL(tile.side[0].previous->value, 30);
}

BOOST_AUTO_TEST_CASE(get_third_side) { // #8
  Tile tile1 = {11, 8, 21, 20, 30, 23, 37, 45, 45};
  double ans = getThirdSide(tile1.side[0], tile1.side[1], tile1.angle[1]);
  BOOST_CHECK_CLOSE(ans, 6.6663, 0.001); // 0.001% is the tolerance
}

BOOST_AUTO_TEST_CASE(get_triangle_area) { // #9
  Tile tile1 = {54, 45, 25, 20, 30, 23, 37, 45, 45};
  double ans = getTriangleArea(tile1.side[0].value, tile1.side[1].value,
                               tile1.side[2].value);
  BOOST_CHECK_CLOSE(ans, 558.5552, 0.001); // 0.001% is the tolerance
}

BOOST_AUTO_TEST_CASE(primitive_tile_add_tile) { // #10
  Tile tile = {10, 7, 21, 20, 20, 54, 54, 45, 45};
  PrimitiveTile newSample(tile);
  Link link1(tile.side[2], tile.side[2]);
  Link link2(tile.side[2], tile.side[0]);
  Link link3(tile.side[0], tile.side[1]);
  Link link4(tile.side[3], tile.side[4]);
  bool answer1 = newSample.isLinkable(link1);
  bool answer2 = newSample.isLinkable(link2);
  bool answer3 = newSample.isLinkable(link3);
  bool answer4 = newSample.isLinkable(link4);
  BOOST_CHECK_EQUAL(answer1, true);
  BOOST_CHECK_EQUAL(answer2, false);
  BOOST_CHECK_EQUAL(answer3, false);
  BOOST_CHECK_EQUAL(answer4, true);
}

BOOST_AUTO_TEST_CASE(drawing_methods) { // #11 There is no test here, just to print the data
  // (5.09,5.80), (1.68,4.90), (0.00,0.00), (5.65,0.00), (7.00,2.83)
  // Tile tile = {5.65, 3.14, 3.53, 3.53, 5.18, 71, 116, 121, 108};
  // Tile tile = {5, 5, 5, 5, 5, 108, 108, 108, 108};
  Tile tile = {32.72, 73.59, 78.67, 49.06, 57.68,122.03,115.73, 84.19, 95.81, 122.23}; // Type 1.1
  // Tile tile = {66, 80, 66, 54, 38.54,106.31,110, 70, 135, 118.69}; // Type 1.2
  double tile_area = getTileArea(tile);
  double p_area = 2 * tile_area; // This is the area of the primitiveTile
  int side_num = 0;
  // PrimitiveTile newSample = new PrimitiveTile;
  // newSample.pentagon = tile;
  PrimitiveTile newSample(tile);
  newSample.drawSquare(p_area);
  newSample.drawPentagon(side_num,side_num);
  Link link1(tile.side[side_num], tile.side[side_num]);
  if (newSample.isLinkable(link1)){
    newSample.drawPentagon(side_num,side_num);
    newSample.doTiling(0,0,0,0);
  }
  // printf("\nNumber of primitive tiles drawn is %d\n", newSample.count);
  double gap = ((25 - newSample.count) * p_area);
  // printf("The gap for the inputted tile is: %f\n\n", gap);
  // newSample.writeToFileRaw();
  // newSample.writeToFile();
}

BOOST_AUTO_TEST_CASE(get_tile_area) { // #12
  Tile tile1 = {5, 5, 5, 5, 5, 108, 108, 108, 108};
  double ans = getTileArea(tile1);
  BOOST_CHECK_CLOSE(ans, 43.01, 0.01); // 0.01% is the tolerance
}

BOOST_AUTO_TEST_CASE(compare_lines_test){ // #13
  Point one = {0,0};
  Point two = {1.12345,2.123};
  Point three = {12.12345,23.123};
  Point four = {1.12345,3.1};
  Line line1 = {one,two};
  Line line2 = {three,four};
  Line line3 = {four,three};
  Line line4 = {four,two};
  BOOST_CHECK_EQUAL(false,  compareLine(line1, line2));
  BOOST_CHECK_EQUAL(true,  compareLine(line3, line2));
  BOOST_CHECK_EQUAL(false,  compareLine(line3, line4));
}

BOOST_AUTO_TEST_CASE(polygon_area_using_shoelace_formula) { // #14
  Tile tile = {5, 5, 5, 5, 5, 108, 108, 108, 108};
  // Tile tile = {5.65, 3.14, 3.53, 3.53, 5.18, 71, 116, 121, 108};
  // Tile tile = {32.72, 73.59, 78.67, 49.06, 57.68,122.03,115.73, 84.19, 95.81,
  // 	       122.23}; // Type 1.1
  double tile_area1 = getTileArea(tile) * 8.0; // 8 Tiles are used here .sooo
  PrimitiveTile newSample(tile);
  newSample.drawPentagon(2, 2);
  newSample.drawPentagon(2, 2);
  newSample.doSimpleTiling(0, 0, 0, 0); // The simple tiling method
  double tile_area2 = getPolygonArea(newSample.lines);
  BOOST_CHECK_CLOSE(tile_area1, tile_area2, 0.5); // The float is the tolerance in percentage
  }

BOOST_AUTO_TEST_CASE(concave_hull) { // #15
  // Tile tile = {5, 5, 5, 5, 5, 108, 108, 108, 108};
  // Tile tile = {5.65, 3.14, 3.53, 3.53, 5.18, 71, 116, 121, 108};
  Tile tile = {32.72, 73.59, 78.67, 49.06, 57.68,122.03,115.73, 84.19, 95.81,
  	       122.23}; // Type 1.1
  double tile_area = getTileArea(tile) * 8.0; // 8 Tiles are used here .sooo
  PrimitiveTile newSample(tile);
  newSample.drawPentagon(2, 2);
  newSample.drawPentagon(2, 2);
  newSample.doSimpleTiling(0, 0, 0, 0); // The simple tiling method
  list<Point_2> list_of_points = getMorePoints(newSample.lines);
  list<Segment> concave_hull = getConcaveHull(list_of_points);
  double whole_area = getPolygonArea(concave_hull);
  double gap = whole_area - tile_area;
  // cout << "Total area of the 8 tiles are: " << tile_area << "\n";
  // cout << "Area of the concave hull is: " << whole_area << "\n";
  // cout << "Gap =  " << gap << "\n";
  // boost  // BOOST_CHECK_CLOSE(gap, 0, 0.5); // The float is the tolerance in percentage
  }

BOOST_AUTO_TEST_CASE(concave_hull_display) { // #16
  // Tile tile = {5, 5, 5, 5, 5, 108, 108, 108, 108};
  Tile tile = {5.65, 3.14, 3.53, 3.53, 5.18, 71, 116, 121, 108};
  // Tile tile = {32.72, 73.59, 78.67, 49.06, 57.68,122.03,115.73, 84.19, 95.81,
  // 	       122.23}; // Type 1.1
  double tile_area1 = getTileArea(tile) * 8.0; // 8 Tiles are used here .sooo
  PrimitiveTile newSample(tile);
  newSample.drawPentagon(2, 2);
  newSample.drawPentagon(2, 2);
  newSample.doSimpleTiling(0, 0, 0, 0); // The simple tiling method
  // newSample.writeToFileRaw();
  list<Line> clean_lines = removeCommonLines(newSample.lines);
  // newSample.writeToFileRaw(clean_lines);
  list<Point_2> list_of_points ;
  list_of_points = getMorePoints(newSample.lines);
  // printData(list_of_points);
  list<Segment> concave_hull = getConcaveHull(list_of_points);
  // printData(concave_hull);
  // newSample.writeToFileRaw(concave_hull);
  }

BOOST_AUTO_TEST_CASE(bounding_box) { // #17
  Tile tile = {5, 5, 5, 5, 5, 108, 108, 108, 108};
  PrimitiveTile newSample(tile);
  newSample.drawPentagon(2, 2);
  newSample.drawPentagon(2, 2);
  newSample.doSimpleTiling(0, 0, 0, 0); // The simple tiling method
  list<Point_2> list_of_points = getSources(newSample.lines);
  Rect box = getBoundingBox(list_of_points);
  // Cout gives the following -1.546 -4.74584 21.1579 24.8939
  BOOST_CHECK_CLOSE(box.xmin(),-1.546 , 0.1);
  BOOST_CHECK_CLOSE(box.ymin(),-4.7458 , 0.1);
  BOOST_CHECK_CLOSE(box.xmax(),21.157 , 0.1);
  BOOST_CHECK_CLOSE(box.ymax(),24.894 , 0.1);
  }

BOOST_AUTO_TEST_CASE(getting_the_biggest_polygon) { // #18
  // Tile tile = {5, 5, 5, 5, 5, 108, 108, 108, 108};
  // Tile tile = {5.65, 3.14, 3.53, 3.53, 5.18, 71, 116, 121, 108};
  Tile tile = {32.72, 73.59, 78.67, 49.06, 57.68,122.03,115.73, 84.19, 95.81,
  	       122.23}; // Type 1.1
  PrimitiveTile newSample(tile);
  newSample.drawPentagon(2, 2);
  newSample.drawPentagon(2, 2);
  newSample.doSimpleTiling(0, 0, 0, 0); // The simple tiling method
  // newSample.writeToFileRaw();
  std::list<Segment> boundary = removeInnerLines(newSample.lines);
  newSample.writeToFileRaw(boundary);
  }
