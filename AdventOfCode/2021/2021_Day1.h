//
// Created by Xeru on 12/1/2021.
//
#pragma once
#include "../AOC.h"
#include <vector>

class AOC_2021_1 : public AdventOfCodeDay {
public:
	std::string GetDataPath() override { return "2021/Data/Day1.txt"; }
	
	void Part1() override;
	void Part2() override;

private:
	int getFrameSum(std::vector<int>& data, int frameEndIndex);
};
