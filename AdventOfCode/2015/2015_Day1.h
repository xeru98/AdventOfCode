#pragma once
#include "../AOC.h"

class AOC_2015_1 : public AdventOfCodeDay {
public:
	std::string GetDataPath() override { return "2015/Data/Day1.txt"; }
	
	void Part1() override;
	void Part2() override;
};