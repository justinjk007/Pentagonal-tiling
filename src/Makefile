test: test.o CalculateGap.o
	g++ -o test test.o CalculateGap.o -lboost_unit_test_framework && ./test

test.o: test.cpp Tile.hpp CalculateGap.hpp
	g++ -c test.cpp

CalculateGap.o: CalculateGap.cpp Tile.hpp CalculateGap.hpp
	g++ -c CalculateGap.cpp

clean:
	rm -f *.o test
	echo Clean done
