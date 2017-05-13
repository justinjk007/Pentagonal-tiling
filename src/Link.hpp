/**
 * This structure connects to tiles(which are pentagons together).
 * This also allows multiple links from one side to many, same way back and forth.
 */
#ifndef LINK_HPP
#define LINK_HPP
#include "Side.hpp"

struct Link
{
  Side* from;
  Side* to;
  Link(Side* connected_from, Side* connected_to){
    this->from = connected_from;
    this->to = connected_to;
  }
};

#endif /* LINK_HPP */
