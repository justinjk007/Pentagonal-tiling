/**
 * This structure connects to tiles(which are pentagons together).
 * This also allows multiple links from one side to many, same way
 * back and forth.
 */
#ifndef LINK_HPP
#define LINK_HPP
#include "Side.hpp"
#include <cstddef> // This library is included so that the NULL pointer works

struct Link
{
  double from;
  double to;
  Link(double connected_from, double connected_to){
    this->from = connected_from;
    this->to = connected_to;
  }
  Link(){
    this->from = 0;
    this->to = 0;
  }
};

#endif /* LINK_HPP */
