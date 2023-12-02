//
// Created by Xeru on 12/1/2021.
//
#pragma once
#include <unordered_map>

#include "../AOC.h"
#include <vector>

class AOC_2023_1 : public AdventOfCodeDay {
public:
	std::string GetDataPath() override { return "2023/Data/Day1.txt"; }
	
	void Part1() override;
	void Part2() override;

private:

	std::unordered_map<std::string, int> NUM_STR = {
		{"zero",		0},
		{"one",		1},
		{"two",		2},
		{"three",		3},
		{"four",		4},
		{"five",		5},
		{"six",		6},
		{"seven",		7},
		{"eight",		8},
		{"nine",		9},
		{"unknown",		-1}
	};
	bool isInt(char c) { return c >= '0' && c <= '9'; }
	long int findNumStr(std::string s);
};
