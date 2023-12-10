#pragma once
#include <unordered_map>
#include <vector>

#include "../AOC.h"

class AOC_2023_7 : public AdventOfCodeDay {
public:
    std::string GetDataPath() override { return "2023/Data/Day7.txt"; }
	
    void Part1() override;
    void Part2() override;

private:

    enum class ScoreClass : uint8_t {
        FiveOfAKind = 7,
        FourOfAKind = 6,
        FullHouse = 5,
        ThreeOfAKind = 4,
        TwoPair = 3,
        OnePair = 2,
        HighCard = 1
    };

    enum class CardValue : uint8_t {
        Joker = 1,
        Two = 2,
        Three = 3,
        Four = 4,
        Five = 5,
        Six = 6,
        Seven = 7,
        Eight = 8,
        Nine = 9,
        Ten = 10,
        Jack = 11,
        Queen = 12,
        King = 13,
        Ace = 14
    };
    
    struct Hand {
        std::vector<CardValue> cards;
        ScoreClass scoreClass;
        long bet;

        bool operator<(const Hand& other);
    };

    static ScoreClass getScoreClassPt1(std::vector<CardValue> values);

    static ScoreClass getScoreClassPt2(std::vector<CardValue> values);
};
