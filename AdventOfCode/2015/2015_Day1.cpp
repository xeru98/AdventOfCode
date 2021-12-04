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

std::string AOC_2015_1::Part1Problem() {
	std::string out = "Santa was hoping for a white Christmas, but his weather machine's \"snow\" \nfunction is powered by stars, and he's fresh out! To save Christmas, he \nneeds you to collect fifty stars by December 25th.\n\n";

	out += "Collect stars by helping Santa solve puzzles. Two puzzles will be made \navailable on each day in the Advent calendar; the second puzzle is unlocked \nwhen you complete the first. Each puzzle grants one star. Good luck!\n\n";

	out += "Here's an easy puzzle to warm you up.\n\n";

	out += "Santa is trying to deliver presents in a large apartment building, but he \ncan't find the right floor - the directions he got are a little confusing. \nHe starts on the ground floor (floor 0) and then follows the instructions \none character at a time.\n\n";

	out += "An opening parenthesis, (, means he should go up one floor, and a closing \nparenthesis, ), means he should go down one floor.\n\n";

	out += "The apartment building is very tall, and the basement is very deep; he will \nnever find the top or bottom floors.\n\n";

	out += "For example:\n\n";

	out += "(()) and ()() both result in floor 0.\n";
	out += "((( and (()(()( both result in floor 3.\n";
	out += "))((((( also results in floor 3.\n";
	out += "()) and ))( both result in floor -1 (the first basement level).\n";
	out += "))) and )())()) both result in floor -3.\n";
	out += "To what floor do the instructions take Santa?\n";
	return out;
}

std::string AOC_2015_1::Part2Problem() {
	std::string out = "Now, given the same instructions, find the position of the first character \nthat causes him to enter the basement (floor -1). The first character in \nthe instructions has position 1, the second character has position 2, and \nso on.\n\n";

	out += "For example:\n\n";

	out += ") causes him to enter the basement at character position 1.\n";
	out += "()()) causes him to enter the basement at character position 5.\n";
	out += "What is the position of the character that causes Santa to first enter the \nbasement?\n";
	return out;
}
