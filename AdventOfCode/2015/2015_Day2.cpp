#include "2015_Day2.h"
#include "../AOCUtils.h"
void AOC_2015_2::Part1() {
	std::vector<Box> data = AdventOfCode::LoadDataFromFile<Box>(GetDataPath(), [](std::string in) {
		std::vector<std::string> parts = AdventOfCode::splitString(in, "x");
		return Box(std::atoi(parts[0].c_str()), std::atoi(parts[1].c_str()), std::atoi(parts[2].c_str()));
	});

	long int totalPaper = 0;
	for(Box b : data) {
		totalPaper += b.GetRequiredPaper();
	}

	std::printf("Total Required Paper: %i", totalPaper);
}

void AOC_2015_2::Part2() {
	std::vector<Box> data = AdventOfCode::LoadDataFromFile<Box>(GetDataPath(), [](std::string in) {
		std::vector<std::string> parts = AdventOfCode::splitString(in, "x");
		return Box(std::atoi(parts[0].c_str()), std::atoi(parts[1].c_str()), std::atoi(parts[2].c_str()));
	});

	long int totalRibbon = 0;
	for(Box b : data) {
		totalRibbon += b.GetRibbonLength();
	}

	std::printf("Total Required Paper: %i", totalRibbon);
}



int AOC_2015_2::Box::GetSurfaceArea() {
	return (2*x*y) + (2*x*z) + (2*y*z);
}

int AOC_2015_2::Box::GetMinFaceArea() {
	return std::min(x*y, std::min(x*z, y*z));
}

int AOC_2015_2::Box::GetRequiredPaper() {
	return GetSurfaceArea() + GetMinFaceArea();
}

int AOC_2015_2::Box::GetRibbonLength() {
	int minHalfPerim = std::min(x+y, std::min(x+z, y+z));
	int extra = x*y*z;
	return (2*minHalfPerim) + extra;
}
