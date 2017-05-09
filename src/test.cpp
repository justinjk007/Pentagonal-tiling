#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GapTest
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "Tile.hpp"
#include "Side.hpp"
#include "CalculateGap.hpp"

using namespace std;

BOOST_AUTO_TEST_CASE(validate){
  Tile tile ={5, 10, 5, 4.3197516, 5, 150, 60, 135, 90};
  BOOST_CHECK_EQUAL(validateTile(tile), true);
}

BOOST_AUTO_TEST_CASE(validate2){ // Complex pentagon
  Tile tile ={3.22, 3.10, 2.20, 2.63, 3.43, 118, 39, 230, 66};
  BOOST_CHECK_EQUAL(validateTile(tile), true);
}

BOOST_AUTO_TEST_CASE(MaxSide){
  Tile tile ={21, 24, 434, 54, 4, 40, 120, 120, 60};
  BOOST_CHECK_EQUAL(getMaxSide(tile), 434);
}

BOOST_AUTO_TEST_CASE(AngleE){
  Tile tile ={21, 24, 434, 54, 4, 40, 120, 120, 60};
  BOOST_CHECK_EQUAL(tile.angle_e, 200);
}

BOOST_AUTO_TEST_CASE( test1){
  Tile tile={10,7,21,20,30,54,54,45,45};
  BOOST_CHECK_EQUAL(tile.side_ab.value, 10);
  BOOST_CHECK_EQUAL(tile.side_ab.next->value, 7);
  BOOST_CHECK_EQUAL(tile.side_ab.previous->value, 30);
}
