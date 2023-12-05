#pragma once
#include "../AOC.h"

class AOC_2023_4 : public AdventOfCodeDay {
public:
    std::string GetDataPath() override { return "2023/Data/Day4.txt"; }
	
    void Part1() override;
    void Part2() override;

private:

    void addOrEmplace(std::map<int, long>& cMap, int key, int numCurrent = 1);
};
