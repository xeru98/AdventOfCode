#pragma once
#include "../AOC.h"
#include <vector>

class AOC_2021_5: public AdventOfCodeDay {
public:
	std::string GetDataPath () override { return "2021/Data/Day5.txt"; }
	void Part1 () override;
	void Part2 () override;
private:

	struct Line {
		std::pair<int, int> start;
		std::pair<int, int> end;

		std::pair<int, int> GetSlopeParts();
		bool IsLineVerticalOrHorizontal();
		std::vector<std::pair<int, int>> GetPoints();
	};

	struct ScanGrid {
		std::vector<std::vector<int>> grid;

		void InitGrid(int rows, int cols);
		void AddPoint(std::pair<int, int> point);
		int GetGridSpacesOverX(int x);
	};
};
