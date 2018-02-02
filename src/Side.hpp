/**
 * This structure defines one side in the pentagon.
 *
 * A Structure is defined instead of just a value in the Tile class
 * because of the added data members like next and previous which
 * might come handy during the final operations.
 */
#ifndef SIDE_HPP
#define SIDE_HPP
#include <cstddef>  // This library is included so that the NULL pointer works

struct Side {
    double value;
    Side() : value(0.0)
    {
    }
    Side(double val) : value(val)
    {
    }
};

#endif /* SIDE_HPP */
