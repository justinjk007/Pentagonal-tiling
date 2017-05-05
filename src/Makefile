test: test.o CalculateGap.o
	g++ -o $@ test.o CalculateGap.o
# && ./test --log_level=test_suite

test.o: test.cpp Tile.hpp CalculateGap.hpp
	g++ -c test.cpp -lboost_unit_test_framework-nt

CalculateGap.o: CalculateGap.cpp Tile.hpp CalculateGap.hpp
	g++ -c CalculateGap.cpp -lboost_unit_test_framework-nt

clean:
	rm -f *.o test
	echo Clean done
