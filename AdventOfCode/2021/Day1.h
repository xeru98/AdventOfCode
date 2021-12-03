//
// Created by Xeru on 12/1/2021.
//
#pragma once
#include "../AOC.h"
#include <vector>

class AOC_2021_1 : public AdventOfCodeDay {
public:
	void Part1() override;
	void Part2() override;

	std::string Part1Problem() override;
	std::string Part2Problem() override;

private:
	int getFrameSum(std::vector<int>& data, int frameEndIndex);
};
