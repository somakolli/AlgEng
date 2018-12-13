//
// Created by sokol on 12.12.18.
//

#include "InvertedIndex.h"
#include <iostream>
#include <fstream>
#include <sstream>

void InvertedIndex::loadIndex() {
	std::cout << "loading file" << std::endl;
	std::ifstream file("/home/sokol/Uni/AlgEng/ir-program/movies.txt");
	if(file.is_open()) {
		std::string line;
		DocumentId id = 0;
		while (getline(file, line)) {
			std::istringstream iss(line);
			std::string word;
			while(iss >> word) {
				index[word].emplace_back(id);
			}
			++id;
		}
		file.close();
	}
}

std::vector<InvertedIndex::DocumentId> InvertedIndex::getIds(std::string queryWord) {
	return index[queryWord];
}
