#pragma once
#include "../AOC.h"

class AOC_2015_2 : public AdventOfCodeDay{
public:
	std::string GetDataPath() override { return "2015/Data/Day2.txt"; }
	void Part1() override;
	void Part2() override;

private:
	struct Box {

		Box(const int x, const int y, const int z)
			:	x(x)
			,	y(y)
			,	z(z)
		{}
		
		int x;
		int y;
		int z;
		int GetSurfaceArea();
		int GetMinFaceArea();
		int GetRequiredPaper();
		int GetRibbonLength();
	};
};
