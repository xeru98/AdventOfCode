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

std::string AOC_2021_2::Part1Problem() {
	std::string out = "Now, you need to figure out how to pilot this thing.\n\n";

	out += "It seems like the submarine can take a series of commands like forward 1, down 2, or up 3:\n\n";

	out += "forward X increases the horizontal position by X units.\n";
	out += "down X increases the depth by X units.\n";
	out += "up X decreases the depth by X units.\n";
	out += "Note that since you're on a submarine, down and up affect your depth, and so they have the opposite result of what you might expect.\n\n";

	out += "The submarine seems to already have a planned course (your puzzle input). You should probably figure out where it's going. For example:\n\n";

	out += "forward 5\n";
	out += "down 5\n";
	out += "forward 8\n";
	out += "up 3\n";
	out += "down 8\n";
	out += "forward 2\n";
	out += "Your horizontal position and depth both start at 0. The steps above would then modify them as follows:\n\n";

	out += "forward 5 adds 5 to your horizontal position, a total of 5.\n";
	out += "down 5 adds 5 to your depth, resulting in a value of 5.\n";
	out += "forward 8 adds 8 to your horizontal position, a total of 13.\n";
	out += "up 3 decreases your depth by 3, resulting in a value of 2.\n";
	out += "down 8 adds 8 to your depth, resulting in a value of 10.\n";
	out += "forward 2 adds 2 to your horizontal position, a total of 15.\n";
	out += "After following these instructions, you would have a horizontal position of 15 and a depth of 10. (Multiplying these together produces 150.)\n\n";

	out += "Calculate the horizontal position and depth you would have after following the planned course. What do you get if you multiply your final horizontal position by your final depth?";
	return out;
}

std::string AOC_2021_2::Part2Problem() {
	std::string out = "Based on your calculations, the planned course doesn't seem to make any sense. You find the submarine manual and discover that the process is actually slightly more complicated.\n\n";

	out += "In addition to horizontal position and depth, you'll also need to track a third value, aim, which also starts at 0. The commands also mean something entirely different than you first thought:\n\n";

	out += "down X increases your aim by X units.\n";
	out += "up X decreases your aim by X units.\n";
	out += "forward X does two things:\n";
	out += "It increases your horizontal position by X units.\n";
	out += "It increases your depth by your aim multiplied by X.\n";
	out += "Again note that since you're on a submarine, down and up do the opposite of what you might expect: \"down\" means aiming in the positive direction.\n\n";

	out += "Now, the above example does something different:\n\n";

	out += "forward 5 adds 5 to your horizontal position, a total of 5. Because your aim is 0, your depth does not change.\n";
	out += "down 5 adds 5 to your aim, resulting in a value of 5.\n";
	out += "forward 8 adds 8 to your horizontal position, a total of 13. Because your aim is 5, your depth increases by 8*5=40.\n";
	out += "up 3 decreases your aim by 3, resulting in a value of 2.\n";
	out += "down 8 adds 8 to your aim, resulting in a value of 10.\n";
	out += "forward 2 adds 2 to your horizontal position, a total of 15. Because your aim is 10, your depth increases by 2*10=20 to a total of 60.\n";
	out += "After following these new instructions, you would have a horizontal position of 15 and a depth of 60. (Multiplying these produces 900.)\n\n";

	out += "Using this new interpretation of the commands, calculate the horizontal position and depth you would have after following the planned course. What do you get if you multiply your final horizontal position by your final depth?";
	return out;
}
