#pragma once
#include "../AOC.h"

class AOC_2021_8 : public AdventOfCodeDay {
public:
	std::string GetDataPath () override { return "2021/Data/Day8.txt"; }
	void Part1 () override;
	void Part2 () override;

private:

	int letterToInt(char c);
	int stringToInt(std::string s);
	int getDecodedDigit(const int values[10], std::string encodedDigit);
	void setPositionCandidates(int positions[7], int positionFlags, int candidateFlags);
	bool isNumberPow2(int n);
};
