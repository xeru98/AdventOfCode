#include "2023_Day12.h"

#include <unordered_set>

#include "../AOCUtils.h"

const std::string test = "2023/Data/test.txt";

void AOC_2023_12::Part1() {
    unsigned long long numVariations = 0;
	AdventOfCode::ProcessDataFromFileInline(test, [this, &numVariations](std::string line) {
		std::vector<std::string> halves = AdventOfCode::splitString(line, " ");
		std::vector<std::string> blockSizeStrs = AdventOfCode::splitString(halves[1], ",");
		std::vector<long> blockSizes;
		for(std::string str : blockSizeStrs) {
			blockSizes.push_back(strtol(str.c_str(), NULL, 10));
		}

		std::unordered_map<std::tuple<int, int, int>, int, hash_fn> memo;
		numVariations += countWaysUtil(halves[0], blockSizes, 0, 0, 0, memo);
		
	});
	printf("Num Variations: %lld", numVariations);
}

void AOC_2023_12::Part2() {
	
}

unsigned long long AOC_2023_12::getNumVariations (const std::string pattern, const std::vector<long> blockSizes) {
	return 0;
}


// Hash function for the tuple (pos, block_idx, in_block)


int AOC_2023_12::countWaysUtil(const std::string& pattern, const std::vector<long>& blockSizes, size_t patternCharIndex, size_t blockIndex, int in_block, std::unordered_map<std::tuple<int, int, int>, int, hash_fn>& memo) {
    if (patternCharIndex == pattern.length()) {
        return blockIndex == blockSizes.size() ? 1 : 0;
    }

    if (pattern[patternCharIndex] == '#') {
        return 0;
    }

    std::tuple<int, int, int> key = std::make_tuple(patternCharIndex, blockIndex, in_block);
    if (memo.find(key) != memo.end()) {
        return memo[key];
    }

    int ways = 0;
    if (pattern[patternCharIndex] == '?') {
        // Option 1: Place a '#'
        if (blockIndex < blockSizes.size() && in_block < blockSizes[blockIndex]) {
            ways += countWaysUtil(pattern, blockSizes, patternCharIndex + 1, blockIndex, in_block + 1, memo);
        }
        // Option 2: Place a '.'
        if (in_block == blockSizes[blockIndex] || pattern[patternCharIndex] == '.') {
            int next_block_idx = in_block == blockSizes[blockIndex] ? blockIndex + 1 : blockIndex;
            ways += countWaysUtil(pattern, blockSizes, patternCharIndex + 1, next_block_idx, 0, memo);
        }
    } else {  // Character is a '.'
        if (in_block == blockSizes[blockIndex]) {
            ways += countWaysUtil(pattern, blockSizes, patternCharIndex + 1, blockIndex + 1, 0, memo);
        } else if (in_block < blockSizes[blockIndex]) {
            ways = 0;  // Invalid case
        }
    }

    memo[key] = ways;
    return ways;
}