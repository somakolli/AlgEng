//
// Created by sokol on 12.12.18.
//

#ifndef IR_PROGRAM_INVERTEDINDEX_H
#define IR_PROGRAM_INVERTEDINDEX_H

#include <unordered_map>
#include <vector>
#include <string>

class InvertedIndex {
	using DocumentId = size_t;
private:
	std::unordered_map<std::string, std::vector<DocumentId>> index;
public:
	void loadIndex();
	std::vector<DocumentId> getIds(std::string queryWord);
private:
};


#endif //IR_PROGRAM_INVERTEDINDEX_H
