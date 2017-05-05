#include <iostream>
#include "Tile.h"

using namespace std;

int main()
{
  Tile test1 = {};
  cout<<test1.angle_a<<endl;
  cout<<test1.side_a<<endl;
  Tile test2 ={21, 54, 54, 54, 4, 40, 120, 120, 60,};

  cout<<"side a of the tile is "<<test2.side_a<<endl;
  cout<<"side b of the tile is "<<test2.side_b<<endl;
  cout<<"side c of the tile is "<<test2.side_c<<endl;
  cout<<"side d of the tile is "<<test2.side_d<<endl;
  cout<<"side e of the tile is "<<test2.side_e<<endl;
  cout<<"Angle A of the tile is "<<test2.angle_a<<endl;
  cout<<"Angle B of the tile is "<<test2.angle_b<<endl;
  cout<<"Angle C of the tile is "<<test2.angle_c<<endl;
  cout<<"Angle D of the tile is "<<test2.angle_d<<endl;
  try{
    if (true)
      throw 001;
  }
  catch(string e){
    cout<<"An exception occured "<<e<<endl;
  }

  try{
    int b=2/0;
  }
  catch(int d){
    cout<<"An exception occured "<<d<<endl;
  } 
}
