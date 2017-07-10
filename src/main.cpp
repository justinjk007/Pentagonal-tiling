#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GapTest
#include "CalculateGap.hpp"
#include "PrimitiveTile.hpp"
#include "Side.hpp"
#include "Tile.hpp"
#include "myGeometry.hpp"
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>
#include <iostream>

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

BOOST_AUTO_TEST_CASE(get_tile_area) { // #10
  Tile tile1 = {5, 5, 5, 5, 5, 108, 108, 108, 108};
  double ans = getTileArea(tile1);
  BOOST_CHECK_CLOSE(ans, 43.01, 0.01); // 0.01% is the tolerance
}

BOOST_AUTO_TEST_CASE(primitive_tile_add_tile) { // #11
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

// BOOST_AUTO_TEST_CASE(my_geometry_line_finder) { // #12
//   Line line1 = {{0, 0}, {4.76, 0.10}};
//   Line line2;
//   line2 = line1.getLineWithRespectTo(49, 3.53,0); // Angle and length

//   BOOST_CHECK_CLOSE(line1.getSlope(), 0.02100840, 0.01);
//   BOOST_CHECK_EQUAL(line1.start.x_cord, 0);
//   BOOST_CHECK_EQUAL(line1.start.y_cord, 0);
//   BOOST_CHECK_EQUAL(line1.end.x_cord, 4.76); //(4.76,0.10)
//   BOOST_CHECK_EQUAL(line1.end.y_cord, 0.10);

//   BOOST_CHECK_CLOSE(line2.getSlope(), 1.201227, 0.01);
//   BOOST_CHECK_CLOSE(line2.start.x_cord, 4.76, 0.01);
//   BOOST_CHECK_CLOSE(line2.start.y_cord, 0.10, 0.01);
//   BOOST_CHECK_CLOSE(line2.end.x_cord, 7.01829, 0.01); //(7.00,2.83)
//   BOOST_CHECK_CLOSE(line2.end.y_cord, 2.812957, 0.01);
// }

BOOST_AUTO_TEST_CASE(test_drawing_methods) { // #13 There is no test here, just to print the data
  // (5.09,5.80), (1.68,4.90), (0.00,0.00), (5.65,0.00), (7.00,2.83)
  // Tile tile = {5.65, 3.14, 3.53, 3.53, 5.18, 71, 116, 121, 108};
  // Tile tile = {5, 5, 5, 5, 5, 108, 108, 108, 108};
  // Tile tile = {32.72, 73.59, 78.67, 49.06, 57.68,122.03,115.73, 84.19, 95.81, 122.23}; // Type 1.1
  Tile tile = {66, 80, 66, 54, 38.54,106.31,110, 70, 135, 118.69}; // Type 1.2
  PrimitiveTile newSample(tile);
  double tile_area = getTileArea(tile);
  double p_area = 2 * tile_area; // This is the area of the primitiveTile
  newSample.drawSquare(p_area);
  int side_num = 1;
  newSample.drawPentagon(side_num,side_num);
  // Link link1(tile.side[side_num], tile.side[side_num]);
  // if (newSample.isLinkable(link1)){
  //   newSample.drawPentagon(side_num,side_num);
  //   newSample.doTiling(0,0,0,0);
  // }
  // double gap = ((25 - newSample.count) * p_area);
  // printf("The gap for the inputted tile is: %f", gap);
  // newSample.writeToFileRaw();
  newSample.writeToFile();
}

// BOOST_AUTO_TEST_CASE(get_gap_the_main_funtion) { // #14
//   Tile tile = {5.65, 3.14, 3.53, 3.53, 5.18, 71, 116, 121, 108};
//   BOOST_CHECK_EQUAL(getGap(tile), 101);
// }
