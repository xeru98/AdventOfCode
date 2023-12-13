#include "2023_Day11.h"

#include <unordered_set>

#include "../AOCUtils.h"

const std::string test = "2023/Data/test.txt";

void AOC_2023_11::Part1() {
    GalaxyMap gMap;
	AdventOfCode::ProcessDataFromFileInline(GetDataPath(), [this, &gMap](std::string line) {
		gMap.numCols = line.size();
		for(int i = 0; i < line.size(); i++) {
			if(line[i] == '#') {
				Point* p = new Point;
				p->x = i;
				p->y = gMap.numRows;
				gMap.galaxies.push_back(p);
			}
		}
		gMap.numRows++;
	});

	timeExpansion(gMap, 2);

	unsigned long long sumDistances = 0;
	const size_t numGalaxies = gMap.galaxies.size();
	for(int src = 0; src < numGalaxies; src++) {
		for(int dst = src+1; dst < numGalaxies; dst++) {
			sumDistances += gMap.galaxies[src]->distanceTo(*gMap.galaxies[dst]);
		}
	}
	printf("Sum Dist: %lld", sumDistances);
}

void AOC_2023_11::Part2() {
	GalaxyMap gMap;
	AdventOfCode::ProcessDataFromFileInline(GetDataPath(), [this, &gMap](std::string line) {
		gMap.numCols = line.size();
		for(int i = 0; i < line.size(); i++) {
			if(line[i] == '#') {
				Point* p = new Point;
				p->x = i;
				p->y = gMap.numRows;
				gMap.galaxies.push_back(p);
			}
		}
		gMap.numRows++;
	});

	timeExpansion(gMap, 1000000);

	unsigned long long sumDistances = 0;
	const size_t numGalaxies = gMap.galaxies.size();
	for(int src = 0; src < numGalaxies; src++) {
		for(int dst = src+1; dst < numGalaxies; dst++) {
			sumDistances += gMap.galaxies[src]->distanceTo(*gMap.galaxies[dst]);
		}
	}
	printf("Sum Dist: %lld", sumDistances);
}

unsigned long long AOC_2023_11::Point::distanceTo (const Point& p) {
	unsigned long long dx = std::max(x,p.x)-std::min(x,p.x);
	unsigned long long dy = std::max(y,p.y)-std::min(y,p.y);
	return dx+dy;
}

void AOC_2023_11::timeExpansion (GalaxyMap& galaxyMap, unsigned long long expansionFactor) {
	std::vector<bool> rowExpansionMask;
	std::vector<bool> colExpansionMask;

	for(int i = 0; i < galaxyMap.numRows; i++) {
		rowExpansionMask.push_back(true);
	}
	for(int i = 0; i < galaxyMap.numCols; i++) {
		colExpansionMask.push_back(true);
	}
	
	for(Point* p : galaxyMap.galaxies) {
		rowExpansionMask[p->y] = false;
		colExpansionMask[p->x] = false;
	}

	std::unordered_map<int, int> rowExpansion;
	std::unordered_map<int, int> colExpansion;
	for(int i = 0; i < galaxyMap.numRows; i++) {
		int last = i == 0 ? 0 : rowExpansion[i-1];
		rowExpansion.emplace(i, last + ((rowExpansionMask[i] ? 1 : 0) * (expansionFactor-1)));
	}
	for(int i = 0; i < galaxyMap.numRows; i++) {
		int last = i == 0 ? 0 : colExpansion[i-1];
		colExpansion.emplace(i, last + ((colExpansionMask[i] ? 1 : 0) * (expansionFactor-1)));
	}

	for(Point* p : galaxyMap.galaxies) {
		p->x += colExpansion[p->x];
		p->y += rowExpansion[p->y];
	}

	galaxyMap.numRows += rowExpansion[galaxyMap.numRows-1];
	galaxyMap.numCols += colExpansion[galaxyMap.numCols-1];
}
