#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GapTest
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "Tile.hpp"
#include "Side.hpp"
#include "CalculateGap.hpp"
#include "PrimitiveTile.hpp"

using namespace std;

BOOST_AUTO_TEST_CASE(validate){
  Tile tile ={5, 10, 5, 4.3197516, 5, 150, 60, 135, 90};
  BOOST_CHECK_EQUAL(validateTile(tile), true);
}

BOOST_AUTO_TEST_CASE(validate2){ // Complex pentagon
  Tile tile ={3.22, 3.10, 2.20, 2.63, 3.43, 118, 39, 330, 66};
  BOOST_CHECK_EQUAL(validateTile(tile), false);
}

BOOST_AUTO_TEST_CASE(max_side_test){
  Tile tile ={21, 24, 434, 54, 4, 40, 120, 120, 60};
  BOOST_CHECK_EQUAL(getMaxSide(tile), 434);
}

BOOST_AUTO_TEST_CASE(AngleE){
  Tile tile ={21, 24, 434, 54, 4, 40, 120, 120, 60};
  BOOST_CHECK_EQUAL(tile.angle_e, 200);
}

BOOST_AUTO_TEST_CASE(tile_values_test){
  Tile tile={10,7,21,20,30,54,54,45,45};
  BOOST_CHECK_EQUAL(tile.side_ab.value, 10);
  BOOST_CHECK_EQUAL(tile.side_ab.next->value, 7);
  BOOST_CHECK_EQUAL(tile.side_ab.previous->value, 30);
}

BOOST_AUTO_TEST_CASE(primitive_tile_test){
  Tile tile={10,7,21,20,30,54,54,45,45};
  PrimitiveTile one(tile);
  BOOST_CHECK_EQUAL(one.checkSide(tile.side_bc), false);
}

BOOST_AUTO_TEST_CASE(get_gap_the_main_funtion){
  Tile tile ={3.22, 3.10, 2.20, 2.63, 3.43, 118, 39, 330, 66};
  BOOST_CHECK_EQUAL(getGap(tile),0);
}

BOOST_AUTO_TEST_CASE(primitive_tile_add_tile){
  Tile tile1={10,7,21,20,30,54,54,45,45};
  Tile tile2={1,17,21,30,40,54,54,45,45};
  Tile tile3={1,17,23,30,40,54,54,45,45};
  PrimitiveTile newSample(tile1);
  Link link1(tile1.side_cd.value,tile2.side_cd.value);
  Link link2(tile1.side_cd.value,tile3.side_cd.value);
  bool answer1 = newSample.addTile(tile2, link1);
  bool answer2 = newSample.addTile(tile3, link2);
  BOOST_CHECK_EQUAL(answer1,true);
  BOOST_CHECK_EQUAL(answer2,false);
  BOOST_CHECK_EQUAL(newSample.size, 2);
  newSample.print();
}
