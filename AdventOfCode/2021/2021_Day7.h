#pragma once
#include <functional>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include "../AOC.h"

class AOC_2021_7 : public AdventOfCodeDay {
public:
	std::string GetDataPath () override { return "2021/Data/Day7.txt"; }
	void Part1 () override;
	void Part2 () override;

private:

	template<typename T>
	T GetTotalCost(std::vector<int> positions, int goal, std::function<T(int, int)> const& costFunction) {
		int total = 0;
		for(int i : positions) {
			total += costFunction(i, goal);
		}
		return total;
	}

	template<typename T>
	T GetMinCost(std::vector<int> positions, std::function<T(int, int)> const& costFunction) {
		std::sort(positions.begin(), positions.end());
		int m = positions[positions.size()/2];
		std::unordered_map<int, T> costMap; //goal index, cost
		costMap[m] = GetTotalCost<T>(positions, m, costFunction);
		costMap[m + 1] = GetTotalCost<T>(positions, m+1, costFunction);
		costMap[m - 1] = GetTotalCost<T>(positions, m-1, costFunction);
		int n = (costMap[m - 1] < costMap[m]) ? m - 1 : (costMap[m + 1] < costMap[m]) ? m + 1 : m;
		if(n == m) {
			return costMap[m];
		}
		int icr = (n == m - 1) ? -1 : 1;
		int p = m;
		while(costMap[n] <= costMap[p]) {
			p = n;
			n += icr;
			costMap[n] = GetTotalCost(positions, n, costFunction);
		}
		return costMap[p];
	}
};
