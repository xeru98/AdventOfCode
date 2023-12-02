//
// Created by Xeru on 12/1/2021.
//
#pragma once
#include <unordered_map>

#include "../AOC.h"
#include <vector>

class AOC_2023_2 : public AdventOfCodeDay {
public:
	std::string GetDataPath() override { return "2023/Data/Day2.txt"; }
	
	void Part1() override;
	void Part2() override;

private:
	
	enum class CubeColor : uint8_t {
		Red,
		Green,
		Blue,
		MAX
	};

	static CubeColor getCubeColor(std::string color);

	static int getMaxCubesPt1(CubeColor color);

	struct Draw {
	public:
		int num;
		CubeColor color;

		Draw(std::string drawStr);
	};

	struct DrawSet {
	public:
		int red = 0;
		int green = 0;
		int blue = 0;

		DrawSet(std::string drawSetStr);

		void addDraw(Draw draw);

		bool isPossiblePt1();
	};

	struct Round {
		long int gameId = 0;
		bool possiblePt1 = true;
		int requiredRed = 0;
		int requiredGreen = 0;
		int requiredBlue = 0;

		Round(std::string roundStr);
		
		void addDrawSet(DrawSet drawSet);

		long getRoundPower();
	};
};
