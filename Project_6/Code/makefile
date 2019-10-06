all: HuffmanTree.o HuffmanTree

HuffmanTree.o: HuffmanTree.cpp HuffmanTree.h
	g++ -c HuffmanTree.cpp

HuffmanTree: HuffmanTree.o main.cpp
	g++ -g HuffmanTree.o main.cpp -o HuffmanTree

clean:
	rm -f *.o
