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

BOOST_AUTO_TEST_CASE(validate) {
  Tile tile = {5, 10, 5, 4.3197516, 5, 150, 60, 135, 90};
  BOOST_CHECK_EQUAL(validateTile(tile), true);
}

BOOST_AUTO_TEST_CASE(validate2) { // Complex pentagon
  Tile tile = {3.22, 3.10, 2.20, 2.63, 3.43, 118, 39, 330, 66};
  BOOST_CHECK_EQUAL(validateTile(tile), false);
}

BOOST_AUTO_TEST_CASE(validate3) {
  Tile tile = {21, 24, 434, 54, 4, 40, 120, 130, 60};
  BOOST_CHECK_EQUAL(validateTile(tile), false);
}

BOOST_AUTO_TEST_CASE(max_side_test) {
  Tile tile = {21, 24, 434, 54, 4, 40, 120, 120, 60};
  BOOST_CHECK_EQUAL(getMaxSide(tile), 434);
}

BOOST_AUTO_TEST_CASE(max_angle_test) {
  Tile tile = {21, 24, 434, 54, 4, 40, 120, 130, 60};
  BOOST_CHECK_EQUAL(getMaxAngle(tile), 190);
}

BOOST_AUTO_TEST_CASE(AngleE) {
  Tile tile = {21, 24, 434, 54, 4, 40, 120, 120, 60};
  BOOST_CHECK_EQUAL(tile.angle[4], 200);
}

BOOST_AUTO_TEST_CASE(get_third_side) {
  Tile tile1 = {11, 8, 21, 20, 30, 23, 37, 45, 45};
  double ans = getThirdSide(tile1.side[0], tile1.side[1], tile1.angle[1]);
  BOOST_CHECK_CLOSE(ans, 6.6663, 0.001); // 0.001% is the tolerance
}

BOOST_AUTO_TEST_CASE(get_triangle_area) {
  Tile tile1 = {54, 45, 25, 20, 30, 23, 37, 45, 45};
  double ans = getTriangleArea(tile1.side[0].value, tile1.side[1].value,
                               tile1.side[2].value);
  BOOST_CHECK_CLOSE(ans, 558.5552, 0.001); // 0.001% is the tolerance
}

BOOST_AUTO_TEST_CASE(primitive_tile_add_tile) {
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

BOOST_AUTO_TEST_CASE(get_tile_area) {
  Tile tile1 = {5.0, 5.0, 5.0, 5.0, 5.0, 108.0, 108.0, 108.0, 108.0};
  double ans = getTileArea(tile1);
  BOOST_CHECK_CLOSE(ans, 43.01, 0.01); // 0.01% is the tolerance
}

BOOST_AUTO_TEST_CASE(compare_lines_test){
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

BOOST_AUTO_TEST_CASE(polygon_area_using_shoelace_formula) {
  Tile tile = {5.0, 5.0, 5.0, 5.0, 5.0, 108.0, 108.0, 108.0, 108.0};
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

BOOST_AUTO_TEST_CASE(bounding_box) {
  Tile tile = {5.0, 5.0, 5.0, 5.0, 5.0, 108.0, 108.0, 108.0, 108.0};
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

BOOST_AUTO_TEST_CASE(getting_the_biggest_polygon) {
  Tile tile = {32.72, 73.59, 78.67, 49.06, 57.68,122.03,115.73, 84.19, 95.81,
  	       122.23}; // Type 1.1
  PrimitiveTile newSample(tile);
  newSample.drawPentagon(2, 2);
  double tile_area = getPolygonArea(newSample.lines) * 8; // Here area of one pentagon * 8
  newSample.drawPentagon(2, 2);
  newSample.doSimpleTiling(0, 0, 0, 0); // The simple tiling method
  // newSample.writeToFileRaw();
  std::list<Segment> boundary        = removeInnerLines(newSample.lines);
  newSample.writeToFileRaw(boundary);
  std::list<Point_2> boundary_points = getSources(boundary);
  boundary_points                    = sortClockwise(boundary_points);
  Polygon_2 p                        = getPolygon(boundary_points);
  double total_area                  = getPolygonArea(boundary_points);
  double total_area_cgal             = p.area();
  BOOST_CHECK_CLOSE(tile_area, total_area, 0.1); // 0.01 is the tolerance %
  }
