#include "2023_Day9.h"

#include "../AOCUtils.h"

const std::string test = "2023/Data/test.txt";

void AOC_2023_9::Part1() {
    unsigned long int PredSum = 0;
    AdventOfCode::ProcessDataFromFileInline(GetDataPath(), [&PredSum](std::string line) {
        std::vector<std::string> parts = AdventOfCode::splitString(line, " ");
        std::vector<std::vector<long>> stages;
        std::vector<long> startValues;
        for(std::string str : parts) {
            startValues.push_back(strtol(str.c_str(), NULL, 10));
        }
        stages.push_back(startValues);

        std::vector<long> lastStage = stages.back();
        //build tree
        while(!allZero(lastStage)) {
            size_t lastStageLen = lastStage.size();
            std::vector<long> nextStage;
            for(int i = 1; i < lastStageLen; i++) {
                nextStage.push_back(lastStage[i] - lastStage[i-1]);
            }
            stages.push_back(nextStage);
            lastStage = stages.back();
        }

        long out = 0;
        for(std::vector<std::vector<long>>::reverse_iterator it = stages.rbegin(); it != stages.rend()-1; ++it) {
            std::vector<long>& next = *(it+1);
            next.push_back(next.back() + (*it).back());
        }
        PredSum += stages[0].back();
    });
    printf("Sum of predictions: %ld", PredSum);
}

void AOC_2023_9::Part2() {
    long long int PredSum = 0;
    AdventOfCode::ProcessDataFromFileInline(GetDataPath(), [&PredSum](std::string line) {
        std::vector<std::string> parts = AdventOfCode::splitString(line, " ");
        std::vector<std::vector<long>> stages;
        std::vector<long> startValues;
        for(std::string str : parts) {
            startValues.push_back(strtol(str.c_str(), NULL, 10));
        }
        stages.push_back(startValues);

        std::vector<long> lastStage = stages.back();
        //build tree
        while(!allZero(lastStage)) {
            size_t lastStageLen = lastStage.size();
            std::vector<long> nextStage;
            for(int i = 1; i < lastStageLen; i++) {
                nextStage.push_back(lastStage[i] - lastStage[i-1]);
            }
            stages.push_back(nextStage);
            lastStage = stages.back();
        }

        long out = 0;
        for(std::vector<std::vector<long>>::reverse_iterator it = stages.rbegin(); it != stages.rend()-1; ++it) {
            std::vector<long>& next = *(it+1);
            long val = next.front() - (*it).front();
            next.insert(next.begin(), val);
        }
        PredSum += stages[0].front();
    });
    printf("Sum of predictions: %ld", PredSum);
}

bool AOC_2023_9::allZero(std::vector<long>& vals) {
    for(long val : vals) {
        if(val != 0) {
            return false;
        }
    }
    return true;
}

