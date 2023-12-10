#pragma once
#include <vector>

#include "../AOC.h"

class AOC_2023_6 : public AdventOfCodeDay {
public:
    std::string GetDataPath() override { return "2023/Data/Day6.txt"; }
	
    void Part1() override;
    void Part2() override;

private:

    template<typename T>
    T getMinHoldTime(T len, T dist);

    template<typename T>
    T getMaxHoldTime(T len, T dist);

    template<typename T>
    bool beatDist(T len, T dist, T holdTime);

    static std::vector<long> getLineInts(std::string line);
};
