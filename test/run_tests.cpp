#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GapTest
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "CalculateGap.hpp"
#include "PrimitiveTile.hpp"
#include "Side.hpp"
#include "Tile.hpp"
#include "boundaryDetection.hpp"
#include "myGeometry.hpp"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;

using namespace std;

BOOST_AUTO_TEST_CASE(validate)
{
    Tile tile = {5, 10, 5, 4.3197516, 5, 150, 60, 135, 90};
    BOOST_CHECK_EQUAL(validateTile(tile), true);
}

BOOST_AUTO_TEST_CASE(validate2)
{  // Complex pentagon
    Tile tile = {3.22, 3.10, 2.20, 2.63, 3.43, 118, 39, 330, 66};
    BOOST_CHECK_EQUAL(validateTile(tile), false);
}

BOOST_AUTO_TEST_CASE(validate3)
{
    Tile tile = {21, 24, 434, 54, 4, 40, 120, 130, 60};
    BOOST_CHECK_EQUAL(validateTile(tile), false);
}

BOOST_AUTO_TEST_CASE(max_side_test)
{
    Tile tile = {21, 24, 434, 54, 4, 40, 120, 120, 60};
    BOOST_CHECK_EQUAL(getMaxSide(tile), 434);
}

BOOST_AUTO_TEST_CASE(max_angle_test)
{
    Tile tile = {21, 24, 434, 54, 4, 40, 120, 130, 60};
    BOOST_CHECK_EQUAL(getMaxAngle(tile), 190);
}

BOOST_AUTO_TEST_CASE(AngleE)
{
    Tile tile = {21, 24, 434, 54, 4, 40, 120, 120, 60};
    BOOST_CHECK_EQUAL(tile.angle[4], 200);
}

BOOST_AUTO_TEST_CASE(get_third_side)
{
    Tile tile1 = {11, 8, 21, 20, 30, 23, 37, 45, 45};
    double ans = getThirdSide(tile1.side[0], tile1.side[1], tile1.angle[1]);
    BOOST_CHECK_CLOSE(ans, 6.6663, 0.001);  // 0.001% is the tolerance
}

BOOST_AUTO_TEST_CASE(get_triangle_area)
{
    Tile tile1 = {54, 45, 25, 20, 30, 23, 37, 45, 45};
    double ans = getTriangleArea(tile1.side[0].value, tile1.side[1].value, tile1.side[2].value);
    BOOST_CHECK_CLOSE(ans, 558.5552, 0.001);  // 0.001% is the tolerance
}

BOOST_AUTO_TEST_CASE(primitive_tile_add_tile)
{
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

// BOOST_AUTO_TEST_CASE(get_tile_area)
// {
//     Tile tile1 = {5.0, 5.0, 5.0, 5.0, 5.0, 108.0, 108.0, 108.0, 108.0};
//     double ans = getTileArea(tile1);
//     BOOST_CHECK_CLOSE(ans, 43.01, 0.01);  // 0.01% is the tolerance
// }

// BOOST_AUTO_TEST_CASE(compare_lines_test)
// {
//     Point one   = {0, 0};
//     Point two   = {1.12345, 2.123};
//     Point three = {12.12345, 23.123};
//     Point four  = {1.12345, 3.1};
//     Line line1  = {one, two};
//     Line line2  = {three, four};
//     Line line3  = {four, three};
//     Line line4  = {four, two};
//     BOOST_CHECK_EQUAL(false, compareLine(line1, line2));
//     BOOST_CHECK_EQUAL(true, compareLine(line3, line2));
//     BOOST_CHECK_EQUAL(false, compareLine(line3, line4));
// }

// BOOST_AUTO_TEST_CASE(create_pentagon_from_7_dimension)
// {
//     Tile tile = {32.72, 73.59, 78.67, 49.06, 115.73, 84.19, 95.81};  // Type 1.1
//     PrimitiveTile newSample(tile);
//     newSample.pentagon = newSample.createPentagon();
//     Tile tile2         = {32.72,  73.59,  78.67, 49.06, 57.68,
// 			  122.03, 115.73, 84.19, 95.81, 122.23};  // Type 1.1
//     BOOST_CHECK_CLOSE(newSample.pentagon.side[0].value, tile2.side[0].value, 0.1);  // The float is the tolerance in percentage
//     BOOST_CHECK_CLOSE(newSample.pentagon.side[1].value, tile2.side[1].value, 0.1);  // The float is the tolerance in percentage
//     BOOST_CHECK_CLOSE(newSample.pentagon.side[2].value, tile2.side[2].value, 0.1);  // The float is the tolerance in percentage
//     BOOST_CHECK_CLOSE(newSample.pentagon.side[3].value, tile2.side[3].value, 0.1);  // The float is the tolerance in percentage
//     BOOST_CHECK_CLOSE(newSample.pentagon.side[4].value, tile2.side[4].value, 0.2);  // TODO: Increase precision
//     BOOST_CHECK_CLOSE(newSample.pentagon.angle[0], tile2.angle[0], 0.1);  // The float is the tolerance in percentage
//     BOOST_CHECK_CLOSE(newSample.pentagon.angle[1], tile2.angle[1], 0.1);  // The float is the tolerance in percentage
//     BOOST_CHECK_CLOSE(newSample.pentagon.angle[2], tile2.angle[2], 0.1);  // The float is the tolerance in percentage
//     BOOST_CHECK_CLOSE(newSample.pentagon.angle[3], tile2.angle[3], 0.1);  // The float is the tolerance in percentage
//     BOOST_CHECK_CLOSE(newSample.pentagon.angle[4], tile2.angle[4], 0.1);  // The float is the tolerance in percentage
// }

// BOOST_AUTO_TEST_CASE(create_pentagon_from_7_dimension_visual)
// {
//     // Tile tile = {5.0, 5.0, 5.0, 5.0, 5.0, 108.0, 108.0, 108.0, 108.0};
//     // Tile tile = {5.65, 3.14, 3.53, 3.53, 5.18, 71, 116, 121, 108};
//     Tile tile = {32.72, 73.59, 78.67, 49.06, 115.73, 84.19, 95.81};  // Type 1.1
//     PrimitiveTile newSample(tile);
//     newSample.pentagon = newSample.createPentagon();
//     newSample.drawPentagon(2, 2);
//     newSample.drawPentagon(2, 2);
//     newSample.doTiling(0, 0, 0, 0);
//     newSample.writeToFileRaw();
//     // newSample.draw();
// }

// BOOST_AUTO_TEST_CASE(polygon_area_using_shoelace_formula)
// {
//     // Tile tile = {5.0, 5.0, 5.0, 5.0, 5.0, 108.0, 108.0, 108.0, 108.0};
//     // Tile tile = {5.65, 3.14, 3.53, 3.53, 5.18, 71, 116, 121, 108};
//     Tile tile         = {32.72,  73.59,  78.67, 49.06, 57.68,
// 			 122.03, 115.73, 84.19, 95.81, 122.23};  // Type 1.1
//     double tile_area1 = getTileArea(tile) * 8.0;                 // 8 Tiles are used here .sooo
//     PrimitiveTile newSample(tile);
//     newSample.drawPentagon(2, 2);
//     newSample.drawPentagon(2, 2);
//     newSample.doTiling(0, 0, 0, 0);
//     // newSample.writeToFileRaw();
//     // newSample.draw();
//     double tile_area2 = getPolygonArea(newSample.lines);
//     BOOST_CHECK_CLOSE(tile_area1, tile_area2, 0.1);  // The float is the tolerance in percentage
// }

// BOOST_AUTO_TEST_CASE(bounding_box)
// {
//     Tile tile = {5.0, 5.0, 5.0, 5.0, 5.0, 108.0, 108.0, 108.0, 108.0};
//     PrimitiveTile newSample(tile);
//     newSample.drawPentagon(2, 2);
//     newSample.drawPentagon(2, 2);
//     newSample.doTiling(0, 0, 0, 0);
//     list<Point_2> list_of_points = getSources(newSample.lines);
//     Rect box                     = getBoundingBox(list_of_points);
//     // Cout gives the following -1.546 -4.74584 21.1579 24.8939
//     BOOST_CHECK_CLOSE(box.xmin(), -1.546, 0.1);
//     BOOST_CHECK_CLOSE(box.ymin(), -4.7458, 0.1);
//     BOOST_CHECK_CLOSE(box.xmax(), 21.157, 0.1);
//     BOOST_CHECK_CLOSE(box.ymax(), 24.894, 0.1);
// }

// BOOST_AUTO_TEST_CASE(getting_the_biggest_polygon)
// {
//     Tile tile = {32.72,  73.59,  78.67, 49.06, 57.68,
//                  122.03, 115.73, 84.19, 95.81, 122.23};  // Type 1.1
//     PrimitiveTile newSample(tile);
//     newSample.drawPentagon(2, 2);
//     double tile_area = getPolygonArea(newSample.lines) * 8.0;  // Here area of one pentagon * 8
//     newSample.drawPentagon(2, 2);
//     newSample.doTiling(0, 0, 0, 0);
//     // newSample.writeToFileRaw();
//     std::list<Segment> boundary = removeInnerLines(newSample.lines);
//     // newSample.writeToFileRaw(boundary);
//     std::list<Point_2> boundary_points = getSources(boundary);
//     boundary_points                    = sortClockwise(boundary_points);
//     double total_area                  = getPolygonArea(boundary_points);
//     BOOST_CHECK_CLOSE(tile_area, total_area, 0.1);  // 0.1 is the tolerance %
// }

// BOOST_AUTO_TEST_CASE(Gap_test_or_Integration_test)
// {
//     Tile tile1 = {32.72,  73.59,  78.67, 49.06, 57.68,
//                   122.03, 115.73, 84.19, 95.81, 122.23};  // Type 1.1
//     double gap1 = getGap(tile1);
//     // cout << "gap1: "<<gap1<<endl;

//     Tile tile2  = {5.0, 5.0, 5.0, 5.0, 5.0, 108.0, 108.0, 108.0, 108.0};
//     double gap2 = getGap(tile2);
//     // cout << "gap2: "<<gap2<<endl;
//     // Points that make up gaps in tile2
//     // (5.0,0.0),(9.04062,2.94506),(10.5746,7.69479),(6.54268,4.75606) These points where found
//     // when debugging using the python script.
//     Point_2 p1(5.0, 0.0), p2(9.04062, 2.94506), p3(10.5746, 7.69479), p4(6.54268, 4.75606);
//     list<Point_2> gap_polygon;
//     gap_polygon.push_back(p1);
//     gap_polygon.push_back(p2);
//     gap_polygon.push_back(p3);
//     gap_polygon.push_back(p4);
//     double gap2_calculated = getPolygonArea(gap_polygon) * 2;  // Two gaps are formed when tiling
//                                                                // this particular tile so the gap
//                                                                // area is multiplied by two.

//     BOOST_CHECK_CLOSE(gap1, 0, 0.1);
//     BOOST_CHECK_CLOSE(gap2, gap2_calculated, 0.5);
// }
