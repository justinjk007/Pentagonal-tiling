all : main run_tests

main: main.o CalculateGap.o PrimitiveTile.o myGeometry.o
	g++ -std=c++11 -g -o main main.o CalculateGap.o PrimitiveTile.o myGeometry.o hullfinder.o

run_tests: run_tests.o CalculateGap.o PrimitiveTile.o myGeometry.o
	g++ -std=c++11 -g -o run_tests run_tests.o CalculateGap.o PrimitiveTile.o myGeometry.o hullfinder.o -lboost_unit_test_framework

main.o: main.cpp CalculateGap.hpp PrimitiveTile.hpp Link.hpp Side.hpp Square.hpp myGeometry.hpp Tile.hpp hullfinder.hpp
	g++ -std=c++11 -c -g main.cpp

run_tests.o: run_tests.cpp CalculateGap.hpp PrimitiveTile.hpp Link.hpp Side.hpp Square.hpp myGeometry.hpp Tile.hpp hullfinder.hpp
	g++ -std=c++11 -c -g run_tests.cpp

CalculateGap.o: CalculateGap.cpp CalculateGap.hpp PrimitiveTile.hpp Link.hpp Side.hpp Square.hpp myGeometry.hpp Tile.hpp hullfinder.hpp
	g++ -std=c++11 -c -g CalculateGap.cpp

PrimitiveTile.o: PrimitiveTile.cpp PrimitiveTile.hpp Link.hpp Side.hpp Square.hpp Tile.hpp myGeometry.hpp CalculateGap.hpp hullfinder.hpp
	g++ -std=c++11 -c -g PrimitiveTile.cpp

myGeometry.o: myGeometry.cpp myGeometry.hpp
	g++ -std=c++11 -c -g myGeometry.cpp

hullfinder.o: hullfinder.cpp hullfinder.hpp
	g++ -std=c++11 -c -g hullfinder.cpp

clean:
	rm -f *.o main run_test
	echo Clean done
