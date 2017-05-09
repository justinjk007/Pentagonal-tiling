#ifndef SIDE_HPP
#define SIDE_HPP

struct Side
{
  double value;
  Side* next;
  Side* previous;
  Side(double val, Side* nex, Side* prev){
    this-> value = val;
    this-> next = nex;
    this-> previous = prev;
  }
};

#endif /* SIDE_HPP */
