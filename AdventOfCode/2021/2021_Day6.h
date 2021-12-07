#pragma once
#include <unordered_map>

#include "../AOC.h"

class AOC_2021_6 : public AdventOfCodeDay {
public:
	std::string GetDataPath () override { return "2021/Data/Day6.txt"; }
	void Part1 () override;
	void Part2 () override;

private:

	template<typename T>
	T GetNumberOfFish(int firstSpawnDay, int maxDay, std::unordered_map<int, T>& spawnMap) {
		if(spawnMap.find(firstSpawnDay) != spawnMap.end()) {
			return spawnMap[firstSpawnDay];
		}
		std::vector<int> directChildrenFSD;
		for(int i = firstSpawnDay; i <= maxDay; i += 7) {
			directChildrenFSD.push_back(i+9);
		}
		T totalSpawn = directChildrenFSD.size();
		for(int fsd : directChildrenFSD) {
			totalSpawn += GetNumberOfFish(fsd, maxDay, spawnMap);
		}
		spawnMap[firstSpawnDay] = totalSpawn;
		return totalSpawn;
	}
};
