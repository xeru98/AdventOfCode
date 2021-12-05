#pragma once
#include "../AOC.h"
#include <vector>

class AOC_2021_4 : public AdventOfCodeDay {
public:
	std::string GetDataPath () override {return "2021/Data/Day4.txt"; }
	void Part1 () override;
	void Part2 () override;
	
private:

	struct BingoBoard {
		int board[5][5];

		BingoBoard();
		BingoBoard(std::vector<std::vector<int>> rows);

		void MarkNumber(int number);
		bool CheckRow(int row);
		bool CheckColumn(int col);
		bool HasBingo();
		int SumBoard();
	};
};
