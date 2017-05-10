test: test.o CalculateGap.o
	g++ -std=c++11 -o test test.o CalculateGap.o PrimitiveTile.o -lboost_unit_test_framework

test.o: test.cpp Tile.hpp Side.hpp CalculateGap.hpp
	g++ -std=c++11 -c test.cpp

CalculateGap.o: CalculateGap.cpp Tile.hpp Side.hpp CalculateGap.hpp
	g++ -std=c++11 -c CalculateGap.cpp

PrimitiveTile.o: PrimitiveTile.cpp PrimitiveTile.hpp Side.hpp
	g++ -std=c++11 -c PrimitiveTile.cpp

clean:
	rm -f *.o test
	echo Clean done
