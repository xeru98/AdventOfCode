#include "2015_Day1.h"
#include "../AOCUtils.h"
void AOC_2015_1::Part1() {
	std::vector<std::vector<char>> data = AdventOfCode::LoadDataFromFile<std::vector<char>>(GetDataPath(), [](std::string in) {
		std::vector<char> out;
		for(char c : in) {
			out.push_back(c);
		}
		return out;
	});

	int floor = 0;
	for(char c : data[0]) {
		if(c == '(') {
			floor += 1;
		} else if (c == ')') {
			floor -= 1;
		}
	}
	std::printf("Floor: %i", floor);
}

void AOC_2015_1::Part2() {
	std::vector<std::vector<char>> data = AdventOfCode::LoadDataFromFile<std::vector<char>>(GetDataPath(), [](std::string in) {
		std::vector<char> out;
		for(char c : in) {
			out.push_back(c);
		}
		return out;
	});

	int index = 0;
	int floor = 0;
	for(int i = 0; i < data[0].size(); i += 1) {
		if(data[0][i] == '(') {
			floor += 1;
		} else if (data[0][i] == ')') {
			floor -= 1;
			if(floor < 0) {
				index = i + 1;
				break;
			}
		}
	}
	std::printf("Index: %i", index);
}

