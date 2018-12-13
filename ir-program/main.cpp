#include <iostream>
#include "InvertedIndex.h"

int main() {
	InvertedIndex invertedIndex;
	invertedIndex.loadIndex();
	for(auto id : invertedIndex.getIds("a"))
		std::cout << ";" << id;
	std::cout << std::endl;
	return 0;
}