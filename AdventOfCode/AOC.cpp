#include "AOC.h"

void AdventOfCodeDay::ExecutePart(int part, bool bShowProblemText) {
	switch(part) {
	case 0:
		if(bShowProblemText) {
			std::printf(Part1Problem().c_str());
		}
		Part1();
		std::printf("\n\n\nPART 2\n");
		if(bShowProblemText) {
			std::printf(Part2Problem().c_str());
		}
		Part2();
	case 1:
		if(bShowProblemText) {
			std::printf(Part1Problem().c_str());
		}
		Part1();
	case 2:
		if(bShowProblemText) {
			std::printf(Part2Problem().c_str());
		}
		Part2();
	default:
		std::printf("Unknown part: %i\n", part);
		break;
	}
}

std::string AdventOfCodeDay::GetProblemText(int part) {
	switch(part) {
	case 0:
		return Part1Problem() + "\n\n\n" + Part2Problem();
	case 1:
		return Part1Problem();
	case 2:
		return Part2Problem();
	default:
		return "Unknown part:" + part;
	}
}
void AdventOfCodeYear::ExecutePart(int day, int part, bool bShowProblemText) {
	if(day == 0) {
		for(std::pair<int, AdventOfCodeDay*> pair : problemMap) {
			pair.second->ExecutePart(part, bShowProblemText);
		}
	} else if(problemMap.find(day) != problemMap.end()) {
		problemMap[day]->ExecutePart(part, bShowProblemText);
	} else {
		std::printf("Unknown Day: %i\n", day);
	}
}

void AdventOfCodeYear::PrintProblemText(int day, int part) {
	if(day == 0) {
		for(std::pair<int, AdventOfCodeDay*> pair : problemMap) {
			std::printf(pair.second->GetProblemText(part).c_str());
		}
	} else if(problemMap.find(day) != problemMap.end()) {
		std::printf(problemMap[day]->GetProblemText(part).c_str());
	} else {
		std::printf("Unknown Day: %i\n", day);
	}
}
