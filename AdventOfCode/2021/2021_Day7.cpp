#include "2021_Day7.h"

#include <algorithm>
#include <unordered_map>

#include "../AOCUtils.h"

void AOC_2021_7::Part1 () {
	std::vector<int> data = AdventOfCode::LoadDataFromFile<std::vector<int>>(GetDataPath(), [](std::string in) {
		std::vector<int> out;
		std::vector<std::string> parts = AdventOfCode::splitString(in, ",");
		for(std::string p : parts) {
			out.push_back(std::atoi(p.c_str()));
		}
		return out;
	})[0];
	
	std::function<int(int, int)> costFunc = [](int s, int g){
		return std::abs(g-s);
	};
	printf("Total Fuel: %i", GetMinCost<int>(data, costFunc));
}
void AOC_2021_7::Part2 () {
	std::vector<int> data = AdventOfCode::LoadDataFromFile<std::vector<int>>(GetDataPath(), [](std::string in) {
		std::vector<int> out;
		std::vector<std::string> parts = AdventOfCode::splitString(in, ",");
		for(std::string p : parts) {
			out.push_back(std::atoi(p.c_str()));
		}
		return out;
	})[0];

	std::function<int(int, int)> costFunc = [](int s, int g) {
		int n = std::abs(s-g);
		return n*(n+1)/2;
	};
	
	printf("Total Fuel: %i", GetMinCost<int>(data, costFunc));
}
