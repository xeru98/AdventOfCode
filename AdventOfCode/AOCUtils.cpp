//
// Created by Xeru on 11/23/2021.
//
#include "AOCUtils.h"

namespace AdventOfCode {
	std::vector<std::string> splitString(std::string searchString, std::string delimiter) {
		std::vector<std::string> out;
		size_t pos = 0;
		while ((pos = searchString.find(delimiter)) != std::string::npos) {
			out.push_back(searchString.substr(0, pos));
			searchString.erase(0, pos + delimiter.length());
		}
		out.push_back(searchString);
		return out;
	}
}
