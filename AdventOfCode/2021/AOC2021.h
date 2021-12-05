#pragma once
#include "../AOC.h"
//Include Days
#include "2021_Day1.h"
#include "2021_Day2.h"
#include "2021_Day3.h"
#include "2021_Day4.h"
#include "2021_Day5.h"

static AdventOfCodeYear AdventOfCode_2021(
	{
		{1, new AOC_2021_1()},
		{2, new AOC_2021_2()},
		{3, new AOC_2021_3()},
		{4, new AOC_2021_4()},
		{5, new AOC_2021_5()}
	}
);
