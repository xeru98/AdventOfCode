//
// Created by Xeru on 12/1/2021.
//
#include "2023_Day2.h"
#include "../AOCUtils.h"

void AOC_2023_2::Part1() {
	long int gameIdSum = 0;
	AdventOfCode::ProcessDataFromFileInline(GetDataPath(), [this, &gameIdSum](std::string line)mutable {
		Round round(line);
		if(round.possiblePt1) {
			gameIdSum += round.gameId;
		}
	});
	printf("GameID Sum: %ld", gameIdSum);
	
}

void AOC_2023_2::Part2() {
	long int cubePower = 0;
	AdventOfCode::ProcessDataFromFileInline(GetDataPath(), [this, &cubePower](std::string line)mutable {
		Round round(line);
		cubePower += round.getRoundPower();
	});
	printf("CubePower: %ld", cubePower);
}

AOC_2023_2::CubeColor AOC_2023_2::getCubeColor(std::string color) {
	if(color.compare("red") == 0) {
		return CubeColor::Red;
	}
	if(color.compare("green") == 0) {
		return CubeColor::Green;
	}
	if(color.compare("blue") == 0) {
		return CubeColor::Blue;
	}
	return CubeColor::MAX;
}

int AOC_2023_2::getMaxCubesPt1(CubeColor color) {
	switch(color) {
	case CubeColor::Red:
		return 12;
	case CubeColor::Green:
		return 13;
	case CubeColor::Blue:
		return 14;
	}
	return 0;
}

AOC_2023_2::Draw::Draw(std::string drawStr) {
	std::vector<std::string> parts = AdventOfCode::splitString(drawStr, " ");
	num = (int) strtol(parts[1].c_str(), NULL, 10);
	color = getCubeColor(parts[2]);
}

AOC_2023_2::DrawSet::DrawSet(std::string drawSetStr) {
	std::vector<std::string> drawStrs = AdventOfCode::splitString(drawSetStr, ",");
	for(const std::string drawStr : drawStrs) {
		addDraw(Draw(drawStr));
	}
}

void AOC_2023_2::DrawSet::addDraw(Draw draw) {
	switch(draw.color) {
	case CubeColor::Red:
		red += draw.num;
		break;
	case CubeColor::Green:
		green += draw.num;
		break;
	case CubeColor::Blue:
		blue += draw.num;
		break;
	}
}

bool AOC_2023_2::DrawSet::isPossiblePt1() {
	return red <= AOC_2023_2::getMaxCubesPt1(CubeColor::Red) &&
			green <= AOC_2023_2::getMaxCubesPt1(CubeColor::Green) &&
			blue <= AOC_2023_2::getMaxCubesPt1(CubeColor::Blue);
}

AOC_2023_2::Round::Round(std::string roundStr) {
	std::vector<std::string> parts = AdventOfCode::splitString(roundStr, ":");
	gameId = strtol(AdventOfCode::splitString(parts[0], " ")[1].c_str(), NULL, 10);
	std::vector<std::string> drawSetStrs = AdventOfCode::splitString(parts[1], ";");
	for(const std::string ds : drawSetStrs) {
		addDrawSet(DrawSet(ds));
	}
}

void AOC_2023_2::Round::addDrawSet(DrawSet drawSet) {
	if(!drawSet.isPossiblePt1()) {
		possiblePt1 = false;
	}
	requiredRed = std::max(requiredRed, drawSet.red);
	requiredGreen = std::max(requiredGreen, drawSet.green);
	requiredBlue = std::max(requiredBlue, drawSet.blue);
}

long AOC_2023_2::Round::getRoundPower() {
	return requiredRed * requiredBlue * requiredGreen;
}
