#pragma once

#include <vector>

#include "../AOC.h"

class AOC_2023_9 : public AdventOfCodeDay {
public:
    std::string GetDataPath() override { return "2023/Data/Day9.txt"; }
	
    void Part1() override;
    void Part2() override;

private:

    static bool allZero(std::vector<long>& vals);
};
