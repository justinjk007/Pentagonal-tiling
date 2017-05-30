test: test.o CalculateGap.o PrimitiveTile.o
	g++ -std=c++11 -g -o test test.o CalculateGap.o PrimitiveTile.o -lboost_unit_test_framework

test.o: test.cpp Tile.hpp Side.hpp CalculateGap.hpp PrimitiveTile.hpp
	g++ -std=c++11 -c -g test.cpp

CalculateGap.o: CalculateGap.cpp Tile.hpp Side.hpp CalculateGap.hpp
	g++ -std=c++11 -c -g CalculateGap.cpp

PrimitiveTile.o: PrimitiveTile.cpp PrimitiveTile.hpp Side.hpp Tile.hpp
	g++ -std=c++11 -c -g PrimitiveTile.cpp

clean:
	rm -f *.o test
	echo Clean done
