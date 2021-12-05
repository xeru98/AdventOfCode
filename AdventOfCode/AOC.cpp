#include "AOC.h"

void AdventOfCodeDay::ExecutePart(int part) {
	switch(part) {
	case 0:
		Part1();
		std::printf("\n\n\nPART 2\n");
		Part2();
		break;
	case 1:
		Part1();
		break;
	case 2:
		Part2();
		break;
	default:
		std::printf("Unknown part: %i\n", part);
		break;
	}
}

void AdventOfCodeYear::ExecutePart(int day, int part) {
	if(day == 0) {
		for(std::pair<int, AdventOfCodeDay*> pair : problemMap) {
			pair.second->ExecutePart(part);
		}
	} else if(problemMap.find(day) != problemMap.end()) {
		problemMap[day]->ExecutePart(part);
	} else {
		std::printf("Unknown Day: %i\n", day);
	}
}
