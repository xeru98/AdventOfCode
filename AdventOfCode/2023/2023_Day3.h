#pragma once
#include "../AOC.h"
#include <vector>

class AOC_2023_3 : public AdventOfCodeDay {
public:
    std::string GetDataPath() override { return "2023/Data/Day3.txt"; }
	
    void Part1() override;
    void Part2() override;

private:

    static const char DOT = '.';
    static inline bool isNumber(char c) {
        return c-'0' >= 0 && c-'0' <= 9;
    }
    static inline bool isSymbol(char c) {
        return c != DOT && !isNumber(c);
    }

    struct PartNumber {
        int row;
        int startCol;
        int endCol;
        std::string valStr;

        PartNumber(int row, int startCol, int endCol)
            : row(row)
            , startCol(startCol)
            , endCol(endCol)
            , valStr("")
        {}

        long val() {
            return strtol(valStr.c_str(), NULL, 10);
        }
    };

    struct PartSymbol {
        int row;
        int col;

        PartSymbol(int row, int col)
            : row(row)
            , col(col)
        {}
    };

    struct Gear : PartSymbol{
        std::vector<PartNumber*> numbers;

        Gear(int row, int col) : PartSymbol(row, col) {}
        
        long ratio() {
            long out = 1;
            for(PartNumber* pn : numbers) {
                out *= pn->val();
            }
            return out;
        }
    };

    bool isAdjacent(PartNumber* pn, PartSymbol* ps);
};
