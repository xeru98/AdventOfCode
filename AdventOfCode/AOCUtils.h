//
// Created by Xeru on 11/23/2021.
//
#pragma once

#include <string>
#include <vector>
#include <functional>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <cassert>

namespace AdventOfCode {

	template<typename T>
	std::vector<T> LoadDataFromFile(const std::string filePath, std::function<T(std::string)> const& parse) {
		std::vector<T> out;
		std::ifstream file(filePath);
		if (file.is_open()) {
			std::string line;
			while (std::getline(file, line)) {
				out.push_back(parse(line));
			}
		}
		return out;
	}

	std::vector<std::string> splitString(std::string searchString, std::string delimiter);

}
