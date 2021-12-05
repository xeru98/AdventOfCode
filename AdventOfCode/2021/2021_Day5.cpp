#include "2021_Day5.h"

#include "../AOCUtils.h"

void AOC_2021_5::Part1 () {
	int maxX = 0;
	int maxY = 0;
	ScanGrid grid;
	std::vector<Line> data = AdventOfCode::LoadDataFromFile<Line>(GetDataPath(), [&maxX, &maxY](std::string in) mutable {
		Line out;
		std::vector<std::string> parts = AdventOfCode::splitString(in, " -> ");
		std::vector<int> points;
		for(std::string s : parts) {
			std::vector<std::string> subParts = AdventOfCode::splitString(s, ",");
			for(std::string sp : subParts) {
				points.push_back(std::atoi(sp.c_str()));
			}
		}
		//if first x is less than second x swap them so all points go from smaller to larger x
		if(points[0] > points[2]) {
			out.start = std::pair<int, int>(points[2], points[3]);
			out.end = std::pair<int, int>(points[0], points[1]);
		} else {
			out.start = std::pair<int, int>(points[0], points[1]);
			out.end = std::pair<int, int>(points[2], points[3]);
		}

		//check for bounderies (start x must always be less than or equal to end x so we don't have to check it)
		if (out.end.first > maxX) {
			maxX = out.end.first;
		}
		if(out.start.second > maxY) {
			maxY = out.start.second;
		}
		if (out.end.second > maxY) {
			maxY = out.end.second;
		}
		
		return out;
	});

	grid.InitGrid(maxY+1, maxX+1);
	
	for(Line l : data) {
		if(l.IsLineVerticalOrHorizontal()) {
			std::vector<std::pair<int , int>> linePoints = l.GetPoints();
			for(std::pair<int, int> point : linePoints) {
				grid.AddPoint(point);
			}
		}
	}

	std::printf("Num spaces: %i", grid.GetGridSpacesOverX(2));

	return;
}

void AOC_2021_5::Part2 () {
	int maxX = 0;
	int maxY = 0;
	ScanGrid grid;
	std::vector<Line> data = AdventOfCode::LoadDataFromFile<Line>(GetDataPath(), [&maxX, &maxY](std::string in) mutable {
		Line out;
		std::vector<std::string> parts = AdventOfCode::splitString(in, " -> ");
		std::vector<int> points;
		for(std::string s : parts) {
			std::vector<std::string> subParts = AdventOfCode::splitString(s, ",");
			for(std::string sp : subParts) {
				points.push_back(std::atoi(sp.c_str()));
			}
		}
		//if first x is less than second x swap them so all points go from smaller to larger x
		if(points[0] > points[2]) {
			out.start = std::pair<int, int>(points[2], points[3]);
			out.end = std::pair<int, int>(points[0], points[1]);
		} else {
			out.start = std::pair<int, int>(points[0], points[1]);
			out.end = std::pair<int, int>(points[2], points[3]);
		}

		//check for bounderies (start x must always be less than or equal to end x so we don't have to check it)
		if (out.end.first > maxX) {
			maxX = out.end.first;
		}
		if(out.start.second > maxY) {
			maxY = out.start.second;
		}
		if (out.end.second > maxY) {
			maxY = out.end.second;
		}
		
		return out;
	});

	grid.InitGrid(maxY+1, maxX+1);
	
	for(Line l : data) {
		std::vector<std::pair<int , int>> linePoints = l.GetPoints();
		for(std::pair<int, int> point : linePoints) {
			grid.AddPoint(point);
		}
	}

	std::printf("Num spaces: %i", grid.GetGridSpacesOverX(2));

	return;
}

//returns as dX, dY (reverse of how it's expected)
std::pair<int, int> AOC_2021_5::Line::GetSlopeParts () {
	return std::pair<int, int>(end.first - start.first, end.second - start.second);
}

bool AOC_2021_5::Line::IsLineVerticalOrHorizontal () {
	std::pair<int, int> slope = GetSlopeParts();
	return slope.first == 0 || slope.second == 0;
}

std::vector<std::pair<int, int>> AOC_2021_5::Line::GetPoints () {
	std::pair<int, int> nextPoint(start.first, start.second);
	std::pair<int, int> slope = GetSlopeParts();
	std::vector<std::pair<int, int>> points;
	
	//if run is 0 then set slope to be vertical
	if(slope.first == 0) {
		if(slope.second > 0) {
			slope.second = 1;
		} else {
			slope.second = -1;
		}
	} else {
		//otherwise just normalize the slope
		slope.second = slope.second/slope.first;
		slope.first = 1;
	}
	
	while(nextPoint != end) {
		points.push_back(nextPoint);
		nextPoint.first += slope.first;
		nextPoint.second += slope.second;
	}
	points.push_back(end);
	return points;
}

void AOC_2021_5::ScanGrid::InitGrid (int rows, int cols) {
	for(int i = 0; i < rows; i += 1) {
		std::vector<int> row;
		for(int j = 0; j < cols; j += 1) {
			row.push_back(0);
		}
		grid.push_back(row);
	}
}

void AOC_2021_5::ScanGrid::AddPoint (std::pair<int, int> point) {
	grid[point.second][point.first] += 1;
}

int AOC_2021_5::ScanGrid::GetGridSpacesOverX (int x) {
	int points = 0;
	for(int i = 0; i < grid.size(); i += 1) {
		for(int j = 0; j < grid[i].size(); j += 1) {
			if(grid[i][j] >= x) {
				points += 1;
			}
		}
	}
	return points;
}
