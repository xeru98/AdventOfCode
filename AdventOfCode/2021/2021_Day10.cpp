#include "2021_Day10.h"

#include <algorithm>
#include <inttypes.h>
#include <stack>

#include "../AOCUtils.h"

void AOC_2021_10::Part1 () {
	std::vector<std::string> data = AdventOfCode::LoadDataFromFile<std::string>(GetDataPath(), [](std::string in) { return in; });
	std::map<char, int> scoreMap = {
		{')', 3},
		{']', 57},
		{'}', 1197},
		{'>', 25137}
	};

	int score = 0;
	for(std::string s: data) {
		std::stack<char> chunkStack;
		for(char c : s) {
			if(isOpeningChar(c)) {
				chunkStack.push(c);
			} else if (isClosingChar(c)) {
				if(isMatchingClosingChar(chunkStack.top(), c)) {
					chunkStack.pop();
				} else {
					score += scoreMap[c];
					break;
				}
			}
		}
	}

	std::printf("Final Score: %i", score);
}

void AOC_2021_10::Part2 () {
	std::vector<std::string> data = AdventOfCode::LoadDataFromFile<std::string>(GetDataPath(), [](std::string in) { return in; });
	std::map<char, int> scoreMap = {
		{')', 1},
		{']', 2},
		{'}', 3},
		{'>', 4}
	};

	std::vector<uintmax_t> scores;
	for(std::string s: data) {
		bool bCorrupted = false;
		uintmax_t score = 0;
		std::stack<char> chunkStack;
		for(char c : s) {
			if(isOpeningChar(c)) {
				chunkStack.push(c);
			} else if (isClosingChar(c)) {
				if(isMatchingClosingChar(chunkStack.top(), c)) {
					chunkStack.pop();
				} else {
					bCorrupted = true;
					break;
				}
			}
		}
		if(bCorrupted) {
			continue;
		}
		int c = chunkStack.size();
		while(!chunkStack.empty()) {
			score *= 5;
			score += scoreMap[getMatchingClosingChar(chunkStack.top())];
			chunkStack.pop();
		}
		scores.push_back(score);
	}

	std::sort(scores.begin(), scores.end());

	std::printf("Scores Size: %llu | Median: %+" SCNiMAX, scores.size(), scores[scores.size()/2]);
}

bool AOC_2021_10::isOpeningChar (char c) {
	return (c == '(') || (c == '[') || (c == '{') || (c == '<');
}

bool AOC_2021_10::isClosingChar (char c) {
	return (c == ')') || (c == ']') || (c == '}') || (c == '>');
}

char AOC_2021_10::getMatchingClosingChar (char openingChar) {
	return chunkMap[openingChar];
}

bool AOC_2021_10::isMatchingClosingChar (char openingChar, char closingChar) {
	return getMatchingClosingChar(openingChar) == closingChar;
}


