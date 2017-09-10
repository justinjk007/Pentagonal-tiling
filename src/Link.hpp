/**
 * This structure connects to tiles(which are pentagons together).
 * This also allows multiple links from one side to many, same way
 * back and forth.
 */
#ifndef LINK_HPP
#define LINK_HPP
#include <cstddef>  // This library is included so that the NULL pointer works
#include "Side.hpp"

struct Link {
    Side from;
    Side to;
    Link()
    {
        Side nullside;
        this->from = nullside;
        this->to   = nullside;
    }
    Link(Side connected_from, Side connected_to)
    {
        this->from = connected_from;
        this->to   = connected_to;
    }
};

#endif /* LINK_HPP */
