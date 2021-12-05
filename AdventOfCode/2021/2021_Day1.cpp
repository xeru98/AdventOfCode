//
// Created by Xeru on 12/1/2021.
//
#include "2021_Day1.h"
#include "../AOCUtils.h"

void AOC_2021_1::Part1() {
	//Load text file into list of integers
	std::vector<int> data = AdventOfCode::LoadDataFromFile<int>(GetDataPath(), [](std::string in){
		return atoi(in.c_str());
	});

	int numIncrements = 0;

	//loop through the list
	for(int i = 1; i < data.size(); i += 1) {
		//if we are being than the index before us then it's deeper
		if(data[i] > data[i-1]) {
			numIncrements += 1;
		}
	}

	std::cout << numIncrements << std::endl;
}

void AOC_2021_1::Part2() {
	//Load text file into list of integers
	std::vector<int> data = AdventOfCode::LoadDataFromFile<int>(GetDataPath(), [](std::string in){
		return atoi(in.c_str());
	});

	int numIncrements = 0;

	//loop through the list
	for(int i = 3; i < data.size(); i += 1) {
		if(getFrameSum(data, i) > getFrameSum(data, i-1)) {
			numIncrements += 1;
		}
	}

	std::cout << numIncrements << std::endl;
}

//Helper to get the sum of the frame in part 2
int AOC_2021_1::getFrameSum(std::vector<int>& data, int frameEndIndex) {
	assert(frameEndIndex >= 2);
	return data[frameEndIndex] + data[frameEndIndex - 1] + data[frameEndIndex - 2];
}
