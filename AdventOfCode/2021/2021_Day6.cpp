#include "2021_Day6.h"

#include <unordered_map>

#include "../AOCUtils.h"

void AOC_2021_6::Part1 () {
	std::vector<int> data = AdventOfCode::LoadDataFromFile<std::vector<int>>(GetDataPath(), [](std::string in) {
		std::vector<int> out;
		std::vector<std::string> parts = AdventOfCode::splitString(in, ",");
		for(std::string p : parts) {
			out.push_back(std::atoi(p.c_str()));
		}
		return out;
	})[0];

	std::unordered_map<int, int> birthChart; //stored as birth day, total fish
	int totalFish = data.size();
	for(int i : data) {
		totalFish += GetNumberOfFish<int>(1 + i, 80, birthChart);
	}
	std::printf("%lld", totalFish);
}

void AOC_2021_6::Part2 () {
	std::vector<int> data = AdventOfCode::LoadDataFromFile<std::vector<int>>(GetDataPath(), [](std::string in) {
		std::vector<int> out;
		std::vector<std::string> parts = AdventOfCode::splitString(in, ",");
		for(std::string p : parts) {
			out.push_back(std::atoi(p.c_str()));
		}
		return out;
	})[0];

	std::unordered_map<int, long long int> birthChart; //stored as birth day, total fish
	long long int totalFish = data.size();
	for(int i : data) {
		totalFish += GetNumberOfFish<long long int>(1 + i, 256, birthChart);
	}
	std::printf("%lld", totalFish);
}
