#include "2023_Day4.h"

#include <set>
#include <unordered_set>
#include <vector>

#include "../AOCUtils.h"

const std::string test = "2023/Data/test.txt";

void AOC_2023_4::Part1() {
    long sum = 0;
    AdventOfCode::ProcessDataFromFileInline(GetDataPath(), [this, &sum](std::string line) mutable {
        std::string numStr = AdventOfCode::splitString(line, ":")[1];
        std::vector<std::string> parts = AdventOfCode::splitString(numStr, "|");
        std::unordered_set<long> winningNumbers;
        for(std::string num : AdventOfCode::splitString(parts[0],  " ")) {
            if(num.length() == 0) {
                continue;
            }
            winningNumbers.emplace(strtol(num.c_str(), NULL, 10));
        }
        long cardScore = 0;
        for(std::string num : AdventOfCode::splitString(parts[1],  " ")) {
            if(num.length() == 0) {
                continue;
            }
            if(winningNumbers.find(strtol(num.c_str(), NULL, 10)) != winningNumbers.end()) {
                if(!cardScore) {
                    cardScore = 1;
                } else {
                    cardScore *= 2;
                }
            }
        }
        sum += cardScore;
    });

    printf("Sum cards: %ld", sum);
}

void AOC_2023_4::Part2() {
    std::map<int, long> cardMap;
    AdventOfCode::ProcessDataFromFileInline(GetDataPath(), [this, &cardMap](std::string line) mutable {
        int cardId = strtol((*(AdventOfCode::splitString(AdventOfCode::splitString(line, ":")[0], " ").end()-1)).c_str(), NULL, 10);
        addOrEmplace(cardMap, cardId);
        
        std::string numStr = AdventOfCode::splitString(line, ":")[1];
        std::vector<std::string> parts = AdventOfCode::splitString(numStr, "|");
        std::unordered_set<long> winningNumbers;
        for(std::string num : AdventOfCode::splitString(parts[0],  " ")) {
            if(num.length() == 0) {
                continue;
            }
            winningNumbers.emplace(strtol(num.c_str(), NULL, 10));
        }
        assert(winningNumbers.size() == 10);
        std::unordered_set<long> nums;
        std::unordered_set<long> matches;
        int numCurrent = cardMap[cardId];
        int matchCount = 0;
        for(std::string num : AdventOfCode::splitString(parts[1],  " ")) {
            if(num.length() == 0) {
                continue;
            }
            long numVal = strtol(num.c_str(), NULL, 10);
            nums.emplace(numVal);
            if(winningNumbers.find(numVal) != winningNumbers.end()) {
                matches.emplace(numVal);
                matchCount++;
                addOrEmplace(cardMap, cardId+matchCount, numCurrent);
            }
        }
        assert(nums.size() == 25);
    });

    long sum = 0;
    for(std::pair<int, long> copy : cardMap) {
        sum += copy.second;
    }
    printf("Total Copies: %ld", sum);
}

void AOC_2023_4::addOrEmplace(std::map<int, long>& cMap, int key, int numCurrent) {
    if(cMap.find(key) == cMap.end()) {
        cMap.emplace(key, numCurrent);
    } else {
        cMap[key] += numCurrent;
    }
}



