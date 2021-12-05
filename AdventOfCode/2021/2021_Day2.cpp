#include "2021_Day2.h"
#include "../AOCUtils.h"

void AOC_2021_2::Part1() {
	int index = 0;
	//Load text file into list of pairs of directions and lengths
	std::vector<std::pair<Direction, int>> data = AdventOfCode::LoadDataFromFile<std::pair<Direction, int>>("Data/Day2.txt", [index](std::string in) mutable{
		std::vector<std::string> parts = AdventOfCode::splitString(in, " ");
		std::pair<Direction, int> out(Direction::unknown, 0);
		if(parts[0].compare("forward") == 0) {
			out.first = Direction::forward;
		} else if (parts[0].compare("up") == 0) {
			out.first = Direction::up;
		} else if (parts[0].compare("down") == 0) {
			out.first = Direction::down;
		} else {
			std::printf("%i : %s\n", index, in.c_str());
		}
		out.second = std::atoi(parts[1].c_str());
		index += 1;
		return out;
	});

	//init vars
	int depth = 0;
	int hpos = 0;

	//loop through data
	for(std::pair<Direction, int> command : data) {
		switch(command.first) {
		case Direction::forward: //move forward
			hpos += command.second;
			break;
		case Direction::up: //decrease depth
			depth -= command.second;
			break;
		case Direction::down: //increase depth
			depth += command.second;
			break;
		default:
			std::cout << "BROKEN" << std::endl;
			break;
		}
	}
	std::printf("HPos: %i, Depth: %i, Total: %i", hpos, depth, hpos*depth);
}

void AOC_2021_2::Part2() {
	int index = 0;
	//Load text file into list of pairs of directions and lengths
	std::vector<std::pair<Direction, int>> data = AdventOfCode::LoadDataFromFile<std::pair<Direction, int>>("Data/Day2.txt", [index](std::string in) mutable{
		std::vector<std::string> parts = AdventOfCode::splitString(in, " ");
		std::pair<Direction, int> out(Direction::unknown, 0);
		if(parts[0].compare("forward") == 0) {
			out.first = Direction::forward;
		} else if (parts[0].compare("up") == 0) {
			out.first = Direction::up;
		} else if (parts[0].compare("down") == 0) {
			out.first = Direction::down;
		} else {
			std::printf("%i : %s\n", index, in.c_str());
		}
		out.second = std::atoi(parts[1].c_str());
		index += 1;
		return out;
	});

	//init vars
	int depth = 0;
	int aim = 0;
	int hpos = 0;

	//Loop through the data
	for(std::pair<Direction, int> command : data) {
		switch(command.first) {
		case Direction::forward:
			hpos += command.second; //move forward
			depth += (command.second * aim); //update depth
			break;
		case Direction::up: //adjust aim up
			aim -= command.second;
			break;
		case Direction::down: //adjust aim down
			aim += command.second;
			break;
		default:
			std::cout << "BROKEN" << std::endl;
			break;
		}
	}
	std::printf("HPos: %i, Depth: %i, Total: %i", hpos, depth, hpos*depth);
}

