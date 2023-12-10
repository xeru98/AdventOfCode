#include "2023_Day6.h"

#include "../AOCUtils.h"

const std::string test = "2023/Data/test.txt";

void AOC_2023_6::Part1() {
    std::vector<std::string> lines = AdventOfCode::LoadDataFromFile<std::string>(GetDataPath(), [](std::string line){return line;});
    std::vector<long> raceLens = getLineInts(lines[0]);
    std::vector<long> raceDist = getLineInts(lines[1]);
    long product = 1;
    for(int i = 0; i < raceLens.size(); i++) {
        long min = getMinHoldTime(raceLens[i], raceDist[i]);
        long max = getMaxHoldTime(raceLens[i], raceDist[i]);
        product *= (max-min)+1;
    }
    printf("Product: %ld", product);
}

void AOC_2023_6::Part2() {
    std::vector<unsigned long long> values = AdventOfCode::LoadDataFromFile<unsigned long long>(GetDataPath(), [](std::string line) {
        std::string valRawStr = AdventOfCode::splitString(line, ":")[1];
        std::string valStr = "";
        for(char c : valRawStr) {
            if(c != ' ') {
                valStr += c;
            }
        }
        return strtoull(valStr.c_str(), NULL, 10);
    });
    unsigned long long min = getMinHoldTime<unsigned long long>(values[0], values[1]);
    unsigned long long max = getMaxHoldTime<unsigned long long>(values[0], values[1]);
    printf("Num Solutions: %ld", max-min + 1);
}

template<typename T>
T AOC_2023_6::getMinHoldTime(T len, T dist) {
    for(T i = 0; i < len; i++) {
        if(beatDist(len, dist, i)) {
            return i;
        }
    }
    return 0;
}

template<typename T>
T AOC_2023_6::getMaxHoldTime(T len, T dist) {
    for(T i = len; i > 0; i--) {
        if(beatDist(len, dist, i)) {
            return i;
        }
    }
    return 0;
}

template<typename T>
bool AOC_2023_6::beatDist(T len, T dist, T holdTime) {
    T travel = holdTime * (len - holdTime);
    return travel > dist;
}

std::vector<long> AOC_2023_6::getLineInts(std::string line) {
    std::vector<long> out;
    std::vector<std::string> parts = AdventOfCode::splitString(line, " ");
    for(std::string part : parts) {
        if(part.size() == 0) {
            continue;
        }
        long val = strtol(part.c_str(), NULL, 10);
        if(val != 0) {
            out.push_back(val);
        }
    }
    return out;
}
