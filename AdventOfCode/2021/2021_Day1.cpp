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

std::string AOC_2021_1::Part1Problem() {
	std::string out ="You're minding your own business on a ship at sea when the overboard alarm goes off! You rush to see if you can help. Apparently, one of the Elves tripped and accidentally sent the sleigh keys flying into the ocean!\n\n";
	out +="Before you know it, you're inside a submarine the Elves keep ready for situations like this. It's covered in Christmas lights (because of course it is), and it even has an experimental antenna that should be able to track the keys if you can boost its signal strength high enough; there's a little meter that indicates the antenna's signal strength by displaying 0-50 stars.\n\n";
	out += "Your instincts tell you that in order to save Christmas, you'll need to get all fifty stars by December 25th.\n\n";
	out +="Collect stars by solving puzzles. Two puzzles will be made available on each day in the Advent calendar; the second puzzle is unlocked when you complete the first. Each puzzle grants one star. Good luck!\n\n";
	out +="As the submarine drops below the surface of the ocean, it automatically performs a sonar sweep of the nearby sea floor. On a small screen, the sonar sweep report (your puzzle input) appears: each line is a measurement of the sea floor depth as the sweep looks further and further away from the submarine.\n\n";
	out += "For example, suppose you had the following report:\n\n";
	out += "199\n200\n208\n210\n200\n207\n240\n269\n260\n263\n";
	out += "This report indicates that, scanning outward from the submarine, the sonar sweep found depths of 199, 200, 208, 210, and so on.\n\n";
	out +="The first order of business is to figure out how quickly the depth increases, just so you know what you're dealing with - you never know if the keys will get carried into deeper water by an ocean current or a fish or something.\n\n";
	out +="To do this, count the number of times a depth measurement increases from the previous measurement. (There is no measurement before the first measurement.) In the example above, the changes are as follows:\n\n";
	out +="199 (N/A - no previous measurement)\n200 (increased)\n208 (increased)\n210 (increased)\n200 (decreased)\n207 (increased)\n240 (increased)\n269 (increased)\n260 (decreased)\n263 (increased)\n";
	out += "In this example, there are 7 measurements that are larger than the previous measurement.\n\n";
	out += "How many measurements are larger than the previous measurement?\n\n";
	return out;
}
std::string AOC_2021_1::Part2Problem() {
	std::string out = "Considering every single measurement isn't as useful as you expected: there's just too much noise in the data.\n\n";
	out += "Instead, consider sums of a three-measurement sliding window. Again considering the above example: \n\n";
	out += "199  A\n200  A B\n208  A B C\n210    B C D\n200  E   C D\n207  E F   D\n240  E F G\n269    F G H\n260      G H\n263        H\n";
	out += "Start by comparing the first and second three-measurement windows. The measurements in the first window are marked A (199, 200, 208); their sum is 199 + 200 + 208 = 607. The second window is marked B (200, 208, 210); its sum is 618. The sum of measurements in the second window is larger than the sum of the first, so this first comparison increased.\n";
	out += "Your goal now is to count the number of times the sum of measurements in this sliding window increases from the previous sum. So, compare A with B, then compare B with C, then C with D, and so on. Stop when there aren't enough measurements left to create a new three-measurement sum.\n";
	out += "In the above example, the sum of each three-measurement window is as follows:\n\n";
	out += "A: 607 (N/A - no previous sum)\nB: 618 (increased)\nC: 618 (no change)\nD: 617 (decreased)\nE: 647 (increased)\nF: 716 (increased)\nG: 769 (increased)\nH: 792 (increased)\n";
	out += "In this example, there are 5 sums that are larger than the previous sum.\n\n";
	out += "Consider sums of a three-measurement sliding window. How many sums are larger than the previous sum?\n";
	return out;
}
