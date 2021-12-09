#include "2021_Day9.h"

#include "../AOCUtils.h"

void AOC_2021_9::Part1 () {
	std::vector<std::vector<int>> data = AdventOfCode::LoadDataFromFile<std::vector<int>>(GetDataPath(), [](std::string in) {
		std::vector<int> out;
		for(char c : in) {
			out.push_back(std::atoi(&c));
		}
		return out;
	});

	int riskLevel = 0;
	//loop through and check each value as being a hot spot
	for(int i = 0; i < data.size(); i += 1) {
		for(int j = 0; j < data[i].size(); j += 1) {
			const int value = data[i][j];
			const int north = (i == 0) ? 10 : data[i-1][j];
			const int south = (i == (data.size() - 1)) ? 10 : data[i+1][j];
			const int east = (j == (data[i].size() - 1)) ? 10 : data[i][j+1];
			const int west = (j == 0) ? 10 : data[i][j-1];
			if(value < north && value < south && value < east && value < west) {
				riskLevel += (value + 1);
			}
		}
	}

	std::printf("Risk Level: %i", riskLevel);
	return;
}

void AOC_2021_9::Part2 () {
	std::vector<std::vector<int>> data = AdventOfCode::LoadDataFromFile<std::vector<int>>(GetDataPath(), [](std::string in) {
		std::vector<int> out;
		for(char c : in) {
			out.push_back(std::atoi(&c));
		}
		return out;
	});

	int largestBasins[3] = {0, 0, 0};

	//loop through all of the squares in the grid
	//since each space < 9 belongs to exactly 1 basin we can clear an entire basin replacing it with 10 after it has been cleared
	for(int i = 0; i < data.size(); i += 1) {
		for(int j = 0; j < data[i].size(); j += 1) {
			if(data[i][j] < 9) {
				//Get basin size and reconfirm largest basins
				int basinSize = clearBasin(data, j, i); //4
				int t = basinSize;
				for(int i = 0; i < 3; i += 1) {
					if(t > largestBasins[i]) {
						int swap = t;
						t = largestBasins[i];
						largestBasins[i] = swap;
					}
				}
			}
		}
	}

	std::printf("Basin Product: %i", largestBasins[0] * largestBasins[1] * largestBasins[2]);
	
}

int AOC_2021_9::clearBasin (std::vector<std::vector<int>>& map, int startX, int startY) {
	int size = 0;
	if(map[startY][startX] >= 9) {
		return 0;
	}

	map[startY][startX] = 10;
	size += 1;
	
	//north
	if(startY != 0) {
		size += clearBasin(map, startX, startY - 1);
	}
	//south
	if(startY != map.size() - 1) {
		size += clearBasin(map, startX, startY + 1);
	}
	//east
	if(startX != map[startY].size() - 1) {
		size += clearBasin(map, startX + 1, startY);
	}
	//west
	if(startX != 0) {
		size += clearBasin(map, startX - 1, startY);
	}
	return size;
}
