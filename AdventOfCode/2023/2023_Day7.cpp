#include "2023_Day7.h"

#include <algorithm>

#include "../AOCUtils.h"

const std::string test = "2023/Data/test.txt";

void AOC_2023_7::Part1() {
    std::vector<Hand> hands = AdventOfCode::LoadDataFromFile<Hand>(GetDataPath(), [](std::string line) {
        std::unordered_map<char, CardValue> CARD_VALUE_MAP = {
            {'2', CardValue::Two},
            {'3', CardValue::Three},
            {'4', CardValue::Four},
            {'5', CardValue::Five},
            {'6', CardValue::Six},
            {'7', CardValue::Seven},
            {'8', CardValue::Eight},
            {'9', CardValue::Nine},
            {'T', CardValue::Ten},
            {'J', CardValue::Jack},
            {'Q', CardValue::Queen},
            {'K', CardValue::King},
            {'A', CardValue::Ace}
        };

        Hand out;
        std::vector<std::string> parts = AdventOfCode::splitString(line, " ");
        out.bet = strtol(parts[1].c_str(), NULL, 10);
        for(char c : parts[0]) {
            out.cards.push_back(CARD_VALUE_MAP[c]);
        }
        out.scoreClass = getScoreClassPt1(out.cards);
        return out;
    });

    std::sort(hands.begin(), hands.end());
    long handSum = 0;
    for(size_t i = 0; i < hands.size(); i++) {
        handSum += (i+1)*hands[i].bet;
    }
    printf("Total Val: %ld", handSum);
}

void AOC_2023_7::Part2() {
    std::vector<Hand> hands = AdventOfCode::LoadDataFromFile<Hand>(GetDataPath(), [](std::string line) {
        std::unordered_map<char, CardValue> CARD_VALUE_MAP = {
            {'J', CardValue::Joker},
            {'2', CardValue::Two},
            {'3', CardValue::Three},
            {'4', CardValue::Four},
            {'5', CardValue::Five},
            {'6', CardValue::Six},
            {'7', CardValue::Seven},
            {'8', CardValue::Eight},
            {'9', CardValue::Nine},
            {'T', CardValue::Ten},
            {'Q', CardValue::Queen},
            {'K', CardValue::King},
            {'A', CardValue::Ace}
        };

        Hand out;
        std::vector<std::string> parts = AdventOfCode::splitString(line, " ");
        out.bet = strtol(parts[1].c_str(), NULL, 10);
        for(char c : parts[0]) {
            out.cards.push_back(CARD_VALUE_MAP[c]);
        }
        out.scoreClass = getScoreClassPt2(out.cards);
        return out;
    });

    std::sort(hands.begin(), hands.end());
    long handSum = 0;
    for(size_t i = 0; i < hands.size(); i++) {
        handSum += (i+1)*hands[i].bet;
    }
    printf("Total Val: %ld", handSum);
}

bool AOC_2023_7::Hand::operator<(const Hand& other) {
    if(scoreClass == other.scoreClass) {
        for(int i = 0; i < 5; i++) {
            if(cards[i] == other.cards[i]) {
                continue;
            }
            return cards[i] < other.cards[i] ? true : false;
        }
    }
    return scoreClass < other.scoreClass ? true : false;
}

AOC_2023_7::ScoreClass AOC_2023_7::getScoreClassPt1(std::vector<CardValue> values) {
    std::unordered_map<CardValue, int> counts;
    for(CardValue value : values) {
        if(counts.find(value) == counts.end()) {
            counts.emplace(value, 0);
        }
        counts[value] += 1;
    }

    
    if(counts.size() == 1) {
        //AAAA
        return ScoreClass::FiveOfAKind;
    }
    if(counts.size() == 2) {
        //AAAAB
        //AAABB
        for(std::pair<CardValue, int> cnt : counts) {
            if(cnt.second == 4) {
                return ScoreClass::FourOfAKind;
            }
        }
        return ScoreClass::FullHouse;
    }
    if(counts.size() == 3) {
        //AAABC
        //AABBC
        for(std::pair<CardValue, int> cnt : counts) {
            if(cnt.second == 3) {
                return ScoreClass::ThreeOfAKind;
            }
        }
        return ScoreClass::TwoPair;
    }
    if(counts.size() == 4) {
        //AABCD
        return ScoreClass::OnePair;
    }
    if(counts.size() == 5) {
        //ABCDE
        return ScoreClass::HighCard;
    }
}

AOC_2023_7::ScoreClass AOC_2023_7::getScoreClassPt2(std::vector<CardValue> values) {
    std::unordered_map<CardValue, int> counts;
    int jokers = 0;
    for(CardValue value : values) {
        if(value == CardValue::Joker) {
            jokers += 1;
            continue;
        }
        if(counts.find(value) == counts.end()) {
            counts.emplace(value, 0);
        }
        counts[value] += 1;
    }

    std::pair<CardValue, int> max = {CardValue::Joker, 0};
    for(std::pair<CardValue, int> cnt : counts) {
        if(cnt.second > max.second) {
            max = cnt;
        } else if(cnt.second == max.second && cnt.first > max.first) {
            max = cnt;
        }
    }

    counts[max.first] += jokers;

    
    if(counts.size() == 1) {
        //AAAA
        return ScoreClass::FiveOfAKind;
    }
    if(counts.size() == 2) {
        //AAAAB
        //AAABB
        for(std::pair<CardValue, int> cnt : counts) {
            if(cnt.second == 4) {
                return ScoreClass::FourOfAKind;
            }
        }
        return ScoreClass::FullHouse;
    }
    if(counts.size() == 3) {
        //AAABC
        //AABBC
        for(std::pair<CardValue, int> cnt : counts) {
            if(cnt.second == 3) {
                return ScoreClass::ThreeOfAKind;
            }
        }
        return ScoreClass::TwoPair;
    }
    if(counts.size() == 4) {
        //AABCD
        return ScoreClass::OnePair;
    }
    if(counts.size() == 5) {
        //ABCDE
        return ScoreClass::HighCard;
    }
}
