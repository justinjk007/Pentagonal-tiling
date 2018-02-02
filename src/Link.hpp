/**
 * This structure connects to tiles(which are pentagons together).
 * This also allows multiple links from one side to many, same way
 * back and forth.
 */
#ifndef LINK_HPP
#define LINK_HPP
#include "Side.hpp"

struct Link {
    Side from;
    Side to;
    Link() : from(Side()), to(Side())
    {
    }
    Link(const Side& connect_from, const Side& connect_to) : from(connect_from), to(connect_to)
    {
    }
};

#endif /* LINK_HPP */
