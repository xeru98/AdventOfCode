#pragma once
#include "../AOC.h"

//Include Days
#include "2023_Day1.h"
#include "2023_Day2.h"
#include "2023_Day3.h"
#include "2023_Day4.h"
#include "2023_Day5.h"

static AdventOfCodeYear AdventOfCode_2023(
	{
		{1, new AOC_2023_1()},
		{2, new AOC_2023_2()},
		{3, new AOC_2023_3()},
		{4, new AOC_2023_4()},
		{5, new AOC_2023_5()}
	}
);
