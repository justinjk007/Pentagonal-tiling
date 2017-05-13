/**
 * This structure defines one pentagon or I am simply calling it a tile.
 */
#ifndef TILE_HPP
#define TILE_HPP
#include "Side.hpp"

struct Tile{
  Side side_ab = {0,&side_bc,&side_ea};
  Side side_bc = {0,&side_cd,&side_ab};
  Side side_cd = {0,&side_de,&side_bc};
  Side side_de = {0,&side_ea,&side_cd};
  Side side_ea = {0,&side_ab,&side_de};
  double angle_a;
  double angle_b;
  double angle_c;
  double angle_d;
  double angle_e;
  Tile(double sab,double sbc,double scd,double sde,double sea,double a,double b,double c,double d){
    this->side_ab.value = sab;
    this->side_bc.value = sbc;
    this->side_cd.value = scd;
    this->side_de.value = sde;
    this->side_ea.value = sea;
    this->angle_a = a;
    this->angle_b = b;
    this->angle_c = c;
    this->angle_d = d;
    this->angle_e = 540-(angle_a+angle_b+angle_c+angle_d);
  }
};

#endif /* TILE_HPP */
