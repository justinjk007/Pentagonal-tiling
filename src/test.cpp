#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GapTest
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "Tile.hpp"
#include "CalculateGap.hpp"

using namespace std;

BOOST_AUTO_TEST_CASE(test1){
  Tile test2 ={21, 54, 54, 54, 4, 40, 120, 120, 60,};
  BOOST_CHECK_EQUAL(getGap(test2), 7.77);
}
