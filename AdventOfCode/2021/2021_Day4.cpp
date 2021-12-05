#include "2021_Day4.h"
#include "../AOCUtils.h"

void AOC_2021_4::Part1 () {
	std::vector<std::vector<int>> data = AdventOfCode::LoadDataFromFile<std::vector<int>>(GetDataPath(), [](std::string in) {
		std::vector<int> out;
		std::vector<std::string> parts;
		if(in.find(' ') != std::string::npos) {
			parts = AdventOfCode::splitString(in, " ");
		} else if(in.find(',') != std::string::npos) {
			parts = AdventOfCode::splitString(in, ",");
		}

		for(std::string p : parts) {
			if(p.length() == 0) {
				continue;
			}
			out.push_back(std::atoi(p.c_str()));
		}
		return out;
	});

	std::vector<int> callSheet = data[0];
	std::vector<BingoBoard> boards;

	for(int i = 1; i < data.size(); i += 5) {
		while(data[i].size() == 0) {
			i += 1;
		}
		boards.push_back(BingoBoard(std::vector<std::vector<int>> {data[i], data[i+1], data[i+2], data[i+3], data[i+4]}));
	}

	for(int n : callSheet) {
		for(BingoBoard& b : boards) {
			b.MarkNumber(n);
			if(b.HasBingo()) {
				std::printf("Found Bingo on call: %i | Remaining Sum: %i | Total: %i", n, b.SumBoard(), n * b.SumBoard());
				return;
			}
		}
	}
}

void AOC_2021_4::Part2 () {
	std::vector<std::vector<int>> data = AdventOfCode::LoadDataFromFile<std::vector<int>>(GetDataPath(), [](std::string in) {
		std::vector<int> out;
		std::vector<std::string> parts;
		if(in.find(' ') != std::string::npos) {
			parts = AdventOfCode::splitString(in, " ");
		} else if(in.find(',') != std::string::npos) {
			parts = AdventOfCode::splitString(in, ",");
		}

		for(std::string p : parts) {
			if(p.length() == 0) {
				continue;
			}
			out.push_back(std::atoi(p.c_str()));
		}
		return out;
	});

	std::vector<int> callSheet = data[0];
	std::vector<BingoBoard> boards;

	for(int i = 1; i < data.size(); i += 5) {
		while(data[i].size() == 0) {
			i += 1;
		}
		boards.push_back(BingoBoard(std::vector<std::vector<int>> {data[i], data[i+1], data[i+2], data[i+3], data[i+4]}));
	}

	for(int n : callSheet) {
		for(int i = 0; i < boards.size();) {
			boards[i].MarkNumber(n);
			if(boards[i].HasBingo()) {
				if(boards.size() == 1) {
					std::printf("Found Bingo on call: %i | Remaining Sum: %i | Total: %i", n, boards[i].SumBoard(), n * boards[i].SumBoard());
					return;
				} else {
					boards.erase(boards.begin() + i);
				}
			} else {
				i += 1;
			}
		}
	}
}

AOC_2021_4::BingoBoard::BingoBoard () {
	for(int i = 0; i < 5; i += 1) {
		for(int j = 0; j < 5; j += 1) {
			board[i][j] = 0;
		}
	}
}

AOC_2021_4::BingoBoard::BingoBoard (std::vector<std::vector<int>> rows) {
	for(int i = 0; i < 5; i += 1) {
		for(int j = 0; j < 5; j += 1) {
			board[i][j] = rows[i][j];
		}
	}
}

void AOC_2021_4::BingoBoard::MarkNumber (int number) {
	for(int i = 0; i < 5; i += 1) {
		for(int j = 0; j < 5; j += 1) {
			if(board[i][j] == number) {
				board[i][j] = 0;
				return;
			}
		}
	}
}

bool AOC_2021_4::BingoBoard::CheckRow (int row) {
	if(row < 0 || row >= 5) {
		return false;
	}
	for(int i = 0; i < 5; i += 1) {
		if(board[row][i] != 0) {
			return false;
		}
	}
	return true;
}

bool AOC_2021_4::BingoBoard::CheckColumn (int col) {
	if(col < 0 || col >= 5) {
		return false;
	}
	for(int i = 0; i < 5; i += 1) {
		if(board[i][col] != 0) {
			return false;
		}
	}
	return true;
}

bool AOC_2021_4::BingoBoard::HasBingo () {
	for(int i = 0; i < 5; i += 1) {
		if(CheckRow(i) || CheckColumn(i)) {
			return true;
		}
	}
	return false;
}

int AOC_2021_4::BingoBoard::SumBoard () {
	int sum = 0;
	for(int i = 0; i < 5; i += 1) {
		for(int j = 0; j < 5; j += 1) {
			sum += board[i][j];
		}
	}
	return sum;
}
