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

std::string AOC_2015_2::Part1Problem() {
	std::string out = "The elves are running low on wrapping paper, and so they need to submit an \norder for more. They have a list of the dimensions (length l, width w, and \nheight h) of each present, and only want to order exactly as much as they \nneed.\n\n";

	out += "Fortunately, every present is a box (a perfect right rectangular prism), \nwhich makes calculating the required wrapping paper for each gift a little \neasier: find the surface area of the box, which is 2*l*w + 2*w*h + 2*h*l. \nThe elves also need a little extra paper for each present: the area of the \nsmallest side.\n\n";

	out += "For example:\n\n";

	out += "A present with dimensions 2x3x4 requires 2*6 + 2*12 + 2*8 = 52 square \nfeet of wrapping paper plus 6 square feet of slack, for a total of 58 \nsquare feet.\n";
	out += "A present with dimensions 1x1x10 requires 2*1 + 2*10 + 2*10 = 42 \nsquare feet of wrapping paper plus 1 square foot of slack, for a total \nof 43 square feet.\n";
	out += "All numbers in the elves' list are in feet. How many total square feet of \nwrapping paper should they order?\n";
	return out;
}

std::string AOC_2015_2::Part2Problem() {
	std::string out = "The elves are also running low on ribbon. Ribbon is all the same width, so \nthey only have to worry about the length they need to order, which they \nwould again like to be exact.\n\n";

out += "The ribbon required to wrap a present is the shortest distance around its \nsides, or the smallest perimeter of any one face. Each present also \nrequires a bow made out of ribbon as well; the feet of ribbon required for \nthe perfect bow is equal to the cubic feet of volume of the present. Don't \nask how they tie the bow, though; they'll never tell.\n\n";

out += "For example:\n";

out += "A present with dimensions 2x3x4 requires 2+2+3+3 = 10 feet of ribbon to wrap the present plus 2*3*4 = 24 feet of ribbon for the bow, for a total of 34 feet.\n";
out += "A present with dimensions 1x1x10 requires 1+1+1+1 = 4 feet of ribbon to wrap the present plus 1*1*10 = 10 feet of ribbon for the bow, for a total of 14 feet.\n";
out += "How many total feet of ribbon should they order?\n";
	return out;
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
