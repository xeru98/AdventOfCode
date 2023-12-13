#pragma once
#include "../AOC.h"

//Include Days
#include "2023_Day1.h"
#include "2023_Day10.h"
#include "2023_Day11.h"
#include "2023_Day12.h"
#include "2023_Day2.h"
#include "2023_Day3.h"
#include "2023_Day4.h"
#include "2023_Day5.h"
#include "2023_Day6.h"
#include "2023_Day7.h"
#include "2023_Day8.h"
#include "2023_Day9.h"

static AdventOfCodeYear AdventOfCode_2023(
	{
		{1, new AOC_2023_1()},
		{2, new AOC_2023_2()},
		{3, new AOC_2023_3()},
		{4, new AOC_2023_4()},
		{5, new AOC_2023_5()},
		{6, new AOC_2023_6()},
		{7, new AOC_2023_7()},
		{8, new AOC_2023_8()},
		{9, new AOC_2023_9()},
		{10, new AOC_2023_10()},
		{11, new AOC_2023_11()},
		{12, new AOC_2023_12()}
	}
);
