#pragma once
#include "../AOC.h"

class AOC_2021_10 : public AdventOfCodeDay {
public:
	std::string GetDataPath () override { return "2021/Data/Day10.txt"; }
	void Part1 () override;
	void Part2 () override;
private:
	inline bool isOpeningChar(char c);
	inline bool isClosingChar(char c);
	inline char getMatchingClosingChar(char openingChar);
	inline bool isMatchingClosingChar(char openingChar, char closingChar);

	std::map<char, char> chunkMap = {
		{'(', ')'},
		{'[', ']'},
		{'{', '}'},
		{'<', '>'}
	};
};
