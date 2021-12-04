//
// Created by Xeru on 12/1/2021.
//
#pragma once
#include "../AOC.h"
#include <vector>

class AOC_2021_2 : public AdventOfCodeDay {
public:
	std::string GetDataPath() override { return "2021/Data/Day2.txt"; }
	
	void Part1() override;
	void Part2() override;

	std::string Part1Problem() override;
	std::string Part2Problem() override;

private:
	enum class Direction {
		forward,
		up,
		down,
		unknown
	};
};
