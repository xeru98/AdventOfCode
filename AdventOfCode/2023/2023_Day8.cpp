#include "2023_Day8.h"

#include <unordered_map>

#include "../AOCUtils.h"

#define LEFT 0
#define RIGHT 1

const std::string test = "2023/Data/test.txt";

void AOC_2023_8::Part1() {
    std::unordered_map<std::string, Node*> nodes;
    std::vector<char> splits;
    AdventOfCode::ProcessDataFromFileInline(GetDataPath(), [&nodes, &splits](std::string line)mutable {
        if(splits.size() == 0) {
            for(char c : line) {
                splits.push_back(c == 'L' ? 0 : 1);
            }
            return;
        }
        if(line.length() == 0) {
            return;
        }

        Node* node = new Node();
        node->value = line.substr(0, 3);
        node->left = line.substr(7, 3);
        node->right = line.substr(12, 3);
        nodes.emplace(node->value, node);
    });

    unsigned long steps = 0;
    const unsigned long len = splits.size();
    Node* next = nodes["AAA"];
    while(next != nodes["ZZZ"]) {
        if(splits[steps % len] == LEFT) {
            next = nodes[next->left];
        } else {
            next = nodes[next->right];
        }
        steps += 1;
    }

    printf("Num Steps: %ld", steps);
}

void AOC_2023_8::Part2() {
    std::unordered_map<std::string, Node*> nodes;
    std::vector<Node*> starts;
    std::vector<char> splits;
    AdventOfCode::ProcessDataFromFileInline(GetDataPath(), [&nodes, &splits, &starts](std::string line)mutable {
        if(splits.size() == 0) {
            for(char c : line) {
                splits.push_back(c == 'L' ? 0 : 1);
            }
            return;
        }
        if(line.length() == 0) {
            return;
        }

        Node* node = new Node();
        node->value = line.substr(0, 3);
        node->left = line.substr(7, 3);
        node->right = line.substr(12, 3);
        nodes.emplace(node->value, node);
        if(isStartNode(node)) {
            starts.push_back(node);
        }
    });
    
    const unsigned long len = splits.size();
    for(Node* node : starts) {
        unsigned long steps = 0;
        while(!isEndNode(node)) {
            if(splits[steps % len] == LEFT) {
                node = nodes[node->left];
            } else {
                node = nodes[node->right];
            }
            steps += 1;
        }
        printf("NumSteps: %ld\n", steps);
    }
}

bool AOC_2023_8::isEndNode(Node* node) {
    return node->value[2] == 'Z';
}

bool AOC_2023_8::isStartNode(Node* node) {
    return node->value[2] == 'A';
}

bool AOC_2023_8::allOnEnd(std::vector<Node*>& nodes) {
    for(Node* node : nodes) {
        if(!isEndNode(node)) {
            return false;
        }
    }
    return true;
}
