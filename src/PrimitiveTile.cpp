#include "PrimitiveTile.hpp"
#include <iostream>

#define SHOW(a) std::cout << #a << " : " << (a) << std::endl
// Macro for variable name;

using namespace std;

bool PrimitiveTile::checkSide(Side side){
  return false;
}

bool PrimitiveTile::addTile(Tile tile,Link link){
  if(!(link.from->value == link.to->value))
    return false;
  else{
    Tile new_tile;
    new_tile = tile;
    this->next = &new_tile;
    links[size] = &link;
    size++;
    return true;
  }
}

void PrimitiveTile::print(){
  cout << "\n";
  for (int i = 1; i < this->size; i++)
    {
      // SHOW(this->links[i]);
      cout << links[i] << endl;
      cout << links[i]->from << endl;
      cout << links[i]->to->value << endl;
      cout << this->links[i]->from->value <<"  "<<links[i]->to->value<<"\n";
    }

}
