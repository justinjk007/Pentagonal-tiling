/**
 * This structure defines one pentagon or I am simply calling it a tile.
 */
#ifndef TILE_HPP
#define TILE_HPP
#include "Side.hpp"

struct Tile {
  Side side[5] = {{0, &side[1], &side[4]},
                  {0, &side[2], &side[0]},
                  {0, &side[3], &side[1]},
                  {0, &side[4], &side[2]},
                  {0, &side[0], &side[3]}};
  double angle_a;
  double angle_b;
  double angle_c;
  double angle_d;
  double angle_e;
  Tile(double sab, double sbc, double scd, double sde, double sea, double a,
       double b, double c, double d) {
    this->side[0].value = sab;
    this->side[1].value = sbc;
    this->side[2].value = scd;
    this->side[3].value = sde;
    this->side[4].value = sea;
    this->angle_a = a;
    this->angle_b = b;
    this->angle_c = c;
    this->angle_d = d;
    this->angle_e = 540 - (angle_a + angle_b + angle_c + angle_d);
  }
  Tile() {
    this->side[0].value = 0;
    this->side[1].value = 0;
    this->side[2].value = 0;
    this->side[3].value = 0;
    this->side[4].value = 0;
    this->angle_a = 0;
    this->angle_b = 0;
    this->angle_c = 0;
    this->angle_d = 0;
    this->angle_e = 0;
  }
};

#endif /* TILE_HPP */
