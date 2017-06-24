main: main.o CalculateGap.o PrimitiveTile.o myGeometry.o
	g++ -std=c++11 -g -o main main.o CalculateGap.o PrimitiveTile.o myGeometry.o -lboost_unit_test_framework

main.o: main.cpp CalculateGap.hpp PrimitiveTile.hpp Link.hpp Side.hpp Square.hpp myGeometry.hpp Tile.hpp
	g++ -std=c++11 -c -g main.cpp

CalculateGap.o: CalculateGap.cpp CalculateGap.hpp PrimitiveTile.hpp Link.hpp Side.hpp Square.hpp myGeometry.hpp Tile.hpp
	g++ -std=c++11 -c -g CalculateGap.cpp

PrimitiveTile.o: PrimitiveTile.cpp PrimitiveTile.hpp Link.hpp Side.hpp Square.hpp Tile.hpp myGeometry.hpp CalculateGap.hpp
	g++ -std=c++11 -c -g PrimitiveTile.cpp

myGeometry.o: myGeometry.cpp myGeometry.hpp
	g++ -std=c++11 -c -g myGeometry.cpp

clean:
	rm -f *.o main
	echo Clean done
