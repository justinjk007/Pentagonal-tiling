
test: test.o CalculateGap.o
	g++ -o test test.o CalculateGap.o

test.o: test.cpp Tile.h CalculateGap.h
	g++ -c test.cpp

CalculateGap.o: CalculateGap.cpp Tile.h CalculateGap.h
	g++ -c CalculateGap.cpp

clean:
	rm -f *.o test
	echo Clean done
