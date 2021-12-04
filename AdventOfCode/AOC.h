#pragma once
#include <map>
#include <string>

#define ALL_PARTS 0
#define ALL_DAYS 0

class AdventOfCodeDay {
public:

	virtual std::string GetDataPath() = 0;
	
	virtual void Part1() = 0;
	virtual void Part2() = 0;
	void ExecutePart(int part = 0, bool bShowProblemText = false);

	
	virtual std::string Part1Problem() = 0;
	virtual std::string Part2Problem() = 0;
	std::string GetProblemText(int part = 0);
};

class AdventOfCodeYear {

private:

	std::map<int, AdventOfCodeDay*> problemMap;

public:

	AdventOfCodeYear(std::map<int, AdventOfCodeDay*> days)
		: problemMap(days)
	{}

	void ExecutePart(int day = 0, int part = 0, bool bShowProblemText = false);
	void PrintProblemText(int day = 0, int part = 0);
};

