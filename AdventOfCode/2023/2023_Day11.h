#pragma once

#include <unordered_map>
#include <set>

#include "../AOC.h"

class AOC_2023_11 : public AdventOfCodeDay {
public:
    std::string GetDataPath() override { return "2023/Data/Day11.txt"; }
	
    void Part1() override;
    void Part2() override;

private:
	
	struct Point {
		unsigned long long x;
		unsigned long long y;

		unsigned long long distanceTo(const Point& p);
	};

	struct GalaxyMap {
		std::vector<Point*> galaxies;

		unsigned long long numRows = 0;
		unsigned long long numCols = 0;
	};

	void timeExpansion(GalaxyMap& galaxyMap, unsigned long long expansionFactor);
};
