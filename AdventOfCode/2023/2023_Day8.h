#pragma once

#include <vector>

#include "../AOC.h"

class AOC_2023_8 : public AdventOfCodeDay {
public:
    std::string GetDataPath() override { return "2023/Data/Day8.txt"; }
	
    void Part1() override;
    void Part2() override;

private:

    struct Node {
        std::string value;
        std::string left;
        std::string right;
    };

    static bool isEndNode(Node* node);
    static bool isStartNode(Node* node);
    static bool allOnEnd(std::vector<Node*>& nodes);
};
