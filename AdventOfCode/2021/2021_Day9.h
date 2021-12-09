#pragma once
#include <vector>

#include "../AOC.h"

class AOC_2021_9 : public AdventOfCodeDay {
public:
	std::string GetDataPath () override { return "2021/Data/Day9.txt"; }
	void Part1 () override;
	void Part2 () override;

private:

	int clearBasin(std::vector<std::vector<int>>& map, int startX, int startY);
};
