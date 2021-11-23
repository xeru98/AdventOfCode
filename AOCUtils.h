//
// Created by Xeru on 11/23/2021.
//
#pragma once

#include <string>
#include <vector>
#include <functional>

namespace AdventOfCode2021 {

template<typename T>
std::vector<T> LoadDataFromFile(const std::string fileName, std::function<T(std::string)>& parse);

std::vector<std::string> splitString(std::string searchString, std::string delimiter);

}
