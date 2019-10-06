all: TriangularMatrix.o TriangularMatrix

TriangularMatrix.o: TriangularMatrix.cpp TriangularMatrix.h
	g++ -c TriangularMatrix.cpp

TriangularMatrix: TriangularMatrix.o main.cpp
	g++ -std=c++11 TriangularMatrix.o main.cpp -o TriangularMatrix

clean:
	rm -f *.o
