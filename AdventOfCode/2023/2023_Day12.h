#pragma once

#include <unordered_map>
#include <set>

#include "../AOC.h"

class AOC_2023_12 : public AdventOfCodeDay {
public:
    std::string GetDataPath() override { return "2023/Data/Day12.txt"; }
	
    void Part1() override;
    void Part2() override;

private:

	unsigned long long getNumVariations(const std::string pattern, const std::vector<long> blockSizes);

	unsigned long long recurse(std::string pattern, std::vector<long> blockSizes, size_t pos, size_t block_idx, size_t in_block);

	struct hash_fn {
		template <class T1, class T2, class T3>
		size_t operator() (const std::tuple<T1, T2, T3>& p) const {
			auto h1 = std::hash<T1>()(std::get<0>(p));
			auto h2 = std::hash<T2>()(std::get<1>(p));
			auto h3 = std::hash<T3>()(std::get<2>(p));
			return h1 ^ h2 ^ h3;
		}
	};

	int countWaysUtil(const std::string& pattern, const std::vector<long>& blockSizes, size_t patternCharIndex, size_t blockIndex, int in_block, std::unordered_map<std::tuple<int, int, int>, int, hash_fn>& memo);

	
};
